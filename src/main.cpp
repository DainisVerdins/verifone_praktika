#include<stdio.h>
#include <cstring>//pause
#include <cctype>//isdigit


#include<vector>
#include<string>

/*
todo list:
FIX MAGICK CONSTANTS NUMBERS
 think about what Range start and range end could be in diferent length;

*/
/**
 * Checks if an target is between low and high.
 * @param {int} low - The integer in question
 * @param {int} high - The integer to compare to
 * @param {int} target - the range
 */
#define MAX_STRING_LENGTH 255
#define MAX_TOKENS 10

struct CardInfo {

	char name[MAX_STRING_LENGTH] = {};
	//ranges are from 1 to 16 digits
	char range_start[16] = {};
	char range_end[16] = {};

	int get_name_length() { return strnlen_s(name, MAX_STRING_LENGTH); }

	//get length of range_start
	int get_range_length() { return strnlen_s(range_start, 16); }

	//return maximal amount of numbers what can contain range
	int get_range_size() { return 16; }
	//return maximal amount of numbers what can contain name
	int get_name_size() { return MAX_STRING_LENGTH; }

};


// Returns true if target in range [low..high], else false
//assumed what inputs are strings with \0
bool in_range(const char* low, const char* high, const char* target)
{
	//probably need to use strncmp, to avoid error if string do not contain \n
	return strcmp(target, low) >= 0 && strcmp(target, high) <= 0;
}


//parses  string into tokens
//be aware pinput_str will be changed on end of operation
int parse_string(char pinput_str[MAX_STRING_LENGTH], const char* delimiter, char* ptoken[MAX_TOKENS])
{
	int i;
	char* pch;
	char* next_token = NULL;

	char key[] = "\r\n";//enter in windows
	i = 0;

	pch = strpbrk(pinput_str, key); //strpbrk
	while (pch != NULL)
	{
		*pch = '\0';
		pch = strpbrk(pch + 1, key);
	}

	ptoken[i] = strtok_s(pinput_str, delimiter, &next_token);
	++i;

	while ((ptoken[i] = strtok_s(NULL, delimiter, &next_token)) != NULL) {

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
	char key[] = "\r\n";

	strcpy_s(buff, MAX_STRING_LENGTH, auth_str);


	/*probably can avoid by jsut using sscanf_s*/

	char* ptoken[MAX_TOKENS];

	number_of_prms = parse_string(buff, ";", ptoken);

	//tokens and what they contain
	//ptoken[0]- range start
	//ptoken[1] - range end
	//ptoken[2] - name
	if (number_of_prms != 3) { return false; }

	if (in_range(ptoken[0], ptoken[1], card_number))
	{

		strcpy_s(card_name, MAX_STRING_LENGTH, ptoken[2]);

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

		printf("cannot find file \"%s\"", file_name);
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
		//TODO: here sleep for 2 seconds
		return false;
	}

}

//check if card_number have valid specifics 
bool is_valid_card_num(const char card_number[])
{
	int card_length = strlen(card_number);
	int i = 0;

	//card number must precisly 16 digits
	const int chars_in_card = 16;//probably to need add as macros

	if (card_length< chars_in_card || card_length>chars_in_card)
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

	int str_sum_length = strlen(inputed_sum);


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

int main()
{
	char file_name[] = "file.txt";
	char card_number[] = "5199999900004646"; //just random number
	CardInfo card;

	if (is_valid_card_num(card_number))
	{
		puts(card_number);

	}
	else {
		printf("bad cards number -> %s\n", card_number);
	}

	char card_name[MAX_STRING_LENGTH];
	if (get_name(file_name, card_number, card_name)) {

		puts(card_name);
	}

	//test cases
	std::vector<std::string>tests{
	"1234.56",//valid
	"123456",
	"1.56",//valid
	"12.56",//valid
	"123.56",//valid
	"56.1234",
	"12341234.56",
	"1234*56",
	"asds.dd",
	"1234.0",
	"123..0",
	".25",
	"1.2",
	"1..2",
	"1.2.",
	"1.22345",
	".2",
	"1234056"
	};

	for (size_t i = 0; i < tests.size(); i++)
	{
		if (is_valid_sum(tests[i].c_str())) {
			printf("%s\n", tests[i].c_str());
		}
	}



	return 0;
}


