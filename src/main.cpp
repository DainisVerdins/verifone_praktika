/*
* Description:
* Programme what promts to user input 16 digits big card number
* if card is valid and found between ranges in database(in this case file.txt file)
* then  promts to write sum(in specific format)
* if all ok with sum writes into file -> card number;name of card(found in DB); entered sum;
*
* Assumed:
* in file.txt data is invariant and in specific format
* format - rangeStart;rangeEnd;Name;
*
* output is in format cardNumber;nameOfCard;EnteredSum;
*
* no negative sum can enter user
*
* @Author
* RazdolbayOne
*/



#include<stdio.h>
#include <string.h>//pause
#include <ctype.h>//isdigit
#include <windows.h> //Sleep()
#include <stdbool.h> //to use bool
#include  <io.h>//_access

#define MAX_STRING_LENGTH 255
#define MAX_TOKENS 10

//how many digits inside range could be 
#define MAX_RANGE_LENGTH 16
#define CARD_NUMBER_LENGTH 16
#define EXIT_SEQUENCE "q"
#define INPUT_FILE_NAME "file.txt"
#define OUTPUT_FILE_NAME "trans.txt"

// Returns true if target in range [low..high], else false
//assumed what inputs are strings with \0 
bool in_range(const char* low, const char* high, const char* target)
{
	//probably need to use strncmp, to avoid error if string do not contain \n
	return strcmp(target, low) >= 0 && strcmp(target, high) <= 0;
}


//parses  string into tokens
//be aware str will be changed on end of operation
int parse_string(char str[MAX_STRING_LENGTH], const char* delimiter, char* token[MAX_TOKENS])
{
	int i;
	char* next_token = NULL;
	i = 0;

	//get rid off new line symbol 
	str[strcspn(str, "\r\n")] = '\0';

	token[i] = strtok_s(str, delimiter, &next_token);
	++i;

	while ((token[i] = strtok_s(NULL, delimiter, &next_token)) != NULL)
	{

		++i;
	}
	return i;

}


//check if card_number is valid for aut_str
//means auth_str contains ranges if card number is between those ranges then is passed. 
//auth_str contains data to check by card number
bool is_auth_passed(const char* auth_str, const char* card_number, char card_name[])
{
	int number_of_prms;
	char buff[MAX_STRING_LENGTH];
	char line_break_symbols[] = "\r\n";

	strcpy_s(buff, MAX_STRING_LENGTH, auth_str);


	/*probably can avoid by jsut using sscanf_s*/

	char* token[MAX_TOKENS];

	number_of_prms = parse_string(buff, ";", token);

	//tokens and what they contain
	//token[0]- range start
	//token[1] - range end
	//token[2] - name
	if (number_of_prms != 3) { return false; }

	if (in_range(token[0], token[1], card_number))
	{

		strcpy_s(card_name, MAX_STRING_LENGTH, token[2]);

		return true;
	}
	return false;
}

//searches card number in files data
//if found returns true and Name of card user
//otherwise false
bool get_name(const char file_name[], const char card_number[], char  card_name[])
{
	FILE* pfile;
	char buff[MAX_STRING_LENGTH];

	fopen_s(&pfile, file_name, "rt");

	if (pfile == NULL) {

		fprintf(stderr, "cannot find file \"%s\"\n", file_name);
		return false;
	}
	else {

		while (fgets(buff, MAX_STRING_LENGTH, pfile) != NULL) {

			if (is_auth_passed(buff, card_number, card_name)) {
				fclose(pfile);
				return true;
			}
		}
		fclose(pfile);
		return false;
	}

}

//writes input card information into file
bool write_card_info(const char file_name[], const char card_number[], const char sum[], const char name[]) {
	FILE* pfile;

	char buff[MAX_STRING_LENGTH];

	// Check for write permission.
	// Assume file is read-only.
	/* modes
	00	Existence only
	02	Write-only
	04	Read-only
	06	Read and write
	*/
	//-1 means true 
	if ((_access(file_name, 2)) == -1) {
		printf_s("File %s does not have write permission.\n", file_name);
		return false;
	}

	fopen_s(&pfile, file_name, "at");

	if (pfile == NULL) {

		printf("error appiered in \"%s\" creation \n", file_name);
		return false;
	}
	else {
		//just in case inputted strings do not have termination symbol
		sprintf_s(buff, MAX_STRING_LENGTH, "%s;%s;%s;", card_number, name, sum);

		fprintf_s(pfile, "%s\n", buff);;

		fclose(pfile);

		return true;
	}

}


//check if card_number have valid specifics 
bool is_valid_card_num(const char card_number[])
{
	const int card_length = (int)strnlen_s(card_number, MAX_STRING_LENGTH);
	int i = 0;


	if (card_length != CARD_NUMBER_LENGTH)
	{
		return false;
	}

	for (i = 0; i < card_length; ++i)
	{
		if (!isdigit(card_number[i]))
		{
			return false;
		}
	}

	return true;
}

//check if inputed sum is in correct format
bool is_valid_sum(const  char inputed_sum[])
{
	/*
		sum format is "nnnn.mm"
		where nnnn - 1 to 4 digits
		mm - 2 digits big sum in cents
		'.' is delimeter
	*/

	const int max_n_count = 4;
	const int min_n_count = 1;
	const int m_count = 2;

	int max_sum_length = max_n_count + m_count + 1;//+1 because delimeter
	int min_sum_length = min_n_count + m_count + 1;
	char delimeter = '.';

	int str_sum_length = (int)strnlen_s(inputed_sum, MAX_STRING_LENGTH);


	if (str_sum_length > max_sum_length || str_sum_length < min_sum_length) {
		return false;
	}

	int delimeter_pos = str_sum_length; //position of out boundry
	//find firs delimeter
	for (int i = 0; i < str_sum_length; i++)
	{
		if (inputed_sum[i] == delimeter) {
			delimeter_pos = i;
			break;
		}
	}
	//in case delimeter not found
	if (delimeter_pos == str_sum_length)
	{
		return false;
	}
	//delimeter_pos+ m_count should target on last index of string
	//str[n-1] is to get last index of string where n is length
	if (delimeter_pos + m_count != str_sum_length - 1)
	{
		return false;
	}

	//check if delimeter is in rigth position
	if (delimeter_pos<min_n_count || delimeter_pos>max_n_count)
	{
		return false;
	}

	//check if n and m part of sum only contain digits
	//if i is delimeter_pos then ignore 
	for (size_t i = 0; i < str_sum_length; i++)
	{
		if (isdigit(inputed_sum[i]) || delimeter_pos == i) {}
		else {
			return false;
		}

	}


	return true;
}

bool is_exit_seq(const char str[]) {

	return  !strcmp(EXIT_SEQUENCE, str);
}

// reading users inputed data
void get_user_input(char input_buff[], const int input_buff_length) {


	fgets(input_buff, input_buff_length, stdin);

	//get rid off new line symbol 
	input_buff[strcspn(input_buff, "\n")] = '\0';

	//clear stdin buffer //probably need to use flush
	rewind(stdin);
}

int main()
{
	char card_name_buff[MAX_STRING_LENGTH];
	//const int input_buff_length = CARD_NUMBER_LENGTH + 1;//plus one because  new line charecter													 
	char input_buff[MAX_STRING_LENGTH];
	const int card_number_size = CARD_NUMBER_LENGTH + 1;//+1 for '\0'
	char card_number[CARD_NUMBER_LENGTH + 1];

	while (true)
	{
		printf("Input precisely 16 digits big card number and press enter\n");
		printf(" or press 'q' and enter to exit.\n");
		printf("if input is longer than 16 digits it will be cut to 16 digits big.\n");


		get_user_input(input_buff, MAX_STRING_LENGTH);

		//exit sequence check
		if (is_exit_seq(input_buff)) { break; }

		if (is_valid_card_num(input_buff))
		{
			//input buff contains credic card number
			if (!get_name(INPUT_FILE_NAME, input_buff, card_name_buff))
			{
				fprintf(stderr, "inputted card number was not found in recordings. Try different one\n");
				Sleep(2000);// 2 seconds
			}
			else {
				//copy from input_buff card number into card_number string
				strcpy_s(card_number, card_number_size, input_buff);

				while (true)
				{
					printf("Enter the sum in format 'nnnn.mm' where:\n");
					printf("'nnnn' – 1 to 4 long sum in euros, \n");
					printf("'mm' – precisely 2 digits sum in cents. ,\n");
					printf("press 'q' and enter to exit.\n");

					//now input_buff contain users imputed sum
					get_user_input(input_buff, MAX_STRING_LENGTH);

					if (is_exit_seq(input_buff)) { break; }


					if (is_valid_sum(input_buff))
					{
						if (write_card_info(OUTPUT_FILE_NAME, card_number, input_buff, card_name_buff)) {
							printf("successfully added\n");
							break;
						}


					}
					else {
						fprintf(stderr, "entered sum did not passed validity test .Try again enter the sum\n");
					}

				}

			}
		}
		else {
			fprintf(stderr, "bad card number \"%s\" Try diferent one\n", input_buff);
		}

	}
	return 0;
}


