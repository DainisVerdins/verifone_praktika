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

	char name[255] = {};
	//ranges are from 1 to 16 digits
	char range_start[16] = {};
	char range_end[16] = {};

	int get_name_length() { return strnlen_s(name, 255); }

	//get length of range_start
	int get_range_length() { return strnlen_s(range_start, 16); }

	//return maximal amount of numbers what can contain range
	int get_range_size() { return 16; }
	//return maximal amount of numbers what can contain name
	int get_name_size() { return 255; }

};


// Returns true if target in range [low..high], else false
//assumed what inputs are strings with \0
bool in_range(const char* low, const char* high, const char* target)
{
	//probably need to use strncmp, to avoid error if string do not contain \n
	return strcmp(target, low) >= 0 && strcmp(target, high) <= 0;
}


//parses  string into tokens
int parse_string(char pinput_str[MAX_STRING_LENGTH], const char* delimiter, char* ptoken[MAX_TOKENS])
{
	//probably can avoid by jsut using sscanf_s
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
bool is_auth_passed(const char* auth_str, const char* card_number)
{
	int number_of_prms;
	char buff[MAX_STRING_LENGTH];
	char key[] = "\r\n";

	strcpy_s(buff, auth_str);

	char* ptoken[MAX_TOKENS];

	number_of_prms = parse_string(buff, ";", ptoken);

	//ptoken[0]- range start
	//ptoken[1] - range end
	//ptoken[2] - name

	printf("%i\n", number_of_prms);
	printf("tokens result\n");
	for (size_t i = 0; i < number_of_prms; i++)
	{
		puts(ptoken[i]);
	}



	printf("\n");

	if (in_range(ptoken[0], ptoken[1], card_number))
	{
		printf("match\n");
		
		return true;
	}
	return false;
}





//searches card number in files data
//if found returns true and Name of card user
//otherwise false
char* get_name(const char file_name[], char card_number[], CardInfo& card)
{

	FILE* pfile;
	char* pname;
	const size_t buff_size = 255;
	pname = NULL;
	char buff[255];


	fopen_s(&pfile, file_name, "rt");

	if (pfile == NULL) {

		printf("cannot find file \"%s\"", file_name);
		return NULL;
	}
	else {

		while (fgets(buff, buff_size, pfile) != NULL) {

			if (is_auth_passed(buff, card_number)) {
				fclose(pfile);
				return pname;
			}
		}
		fclose(pfile);
		//TODO: here sleep for 2 seconds
		return pname;
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





	return false;
}

int main()
{
	char file_name[] = "file.txt";
	char card_number[] = "9999999900004646"; //just random number
	CardInfo card;

	if (is_valid_card_num(card_number))
	{
		puts(card_number);

	}
	else {
		printf("bad cards number -> %s\n", card_number);
	}


	get_name(file_name, card_number, card);
	////test cases
	//std::vector<std::string>tests{
	//"1234.56",//valid
	//"1.56",//valid
	//"56.1234",
	//"12341234.56",
	//"1234*56",
	//"asds.dd",
	//"1234.0",
	//"123..0",
	//".25",
	//"1.2",
	//"1.22345"
	//".2",
	//};

	//for (size_t i = 0; i < 9; i++)
	//{
	//	if (is_valid_sum(tests[i].c_str())) {
	//		printf("%s\n", tests[i].c_str());
	//	}
	//}



	return 0;
}


