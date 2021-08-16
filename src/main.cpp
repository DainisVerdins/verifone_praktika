#include<stdio.h>
#include <cstring>//pause
#include <cctype>//isdigit


#define STR_BUFFER_SIZE 255


char* get_names(char* str, char* card_number)
{
	const size_t range_size = 16;
	char range_start[range_size] = {};
	char range_end[range_size] = {};

	const size_t name_size = 255;
	char card_name[name_size];//buffer what contains name;



	//get separating string into parts/
	char* token;
	const char* delim = ";";
	char* next_token=NULL;
	printf("Parsing the input str [%s] \n", str);
	printf("\n");
	token = strtok_s(str,  delim, &next_token);
	puts(token);
	token = strtok_s(NULL, delim, &next_token);
	puts(token);
	token = strtok_s(NULL, delim, &next_token);
	puts(token);
	


	return card_number;
}





//searches card number in files data
//if found returns true and Name of card user
//otherwise false
char* get_name(const char file_name[], char card_number[])
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
			printf("%s", buff);

			pname = get_names(buff, card_number);
		}

		fclose(pfile);
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


int main()
{
	char file_name[] = "file.txt";
	char card_number[] = "1234567890123456"; //just random number
	char test_account_info[] = "400000000000;499999999999;VISA;"; //25 29

	if (is_valid_card_num(card_number))
	{
		puts(card_number);

	}
	else {
		printf("bad cards number -> %s\n", card_number);
	}


	get_name(file_name, card_number);



	return 0;
}
