#include<stdio.h>
#include <cstring>//pause
#include <cctype>//isdigit
/*
todo list:
FIX MAGICK CONSTANTS NUMBERS

*/

#define STR_BUFFER_SIZE 255


struct CardInfo {

	char name[255] = {};
	char range_start[16] = {};
	char range_end[16] = {};
	bool found = false; //FIX

	int get_name_length() { return strnlen_s(name,255); }
	
	//get length of range_start
	int get_range_length() { return strnlen_s(range_start,16); }

	//return maximal amount of numbers what can contain range
	int get_range_size() { return 16; }
	//return maximal amount of numbers what can contain name
	int get_name_size() { return 255; }
	
};



void get_names(const char* str, const char* card_number)
{
	// TODO think about what Range start and range end could be in diferent length;
	int i;
	CardInfo card;
	
	
	sscanf_s(str, "%[0-9];%[0-9];%[a-zA-Z];",card.range_start, card.get_range_size(),
											 card.range_end, card.get_range_size(),
											 card.name, card.get_name_size());

	puts("\n");

	for ( i = 0; i < card.get_range_length(); ++i)
	{
		if (card.range_start[i]> card_number[i] || card.range_end[i] < card_number[i])
		{
			printf("no match");
			return;
		}
	}
	printf("match\n");
	puts(card.range_start);
	puts(card_number);
	puts(card.range_end);
	puts(card.name);
	//proverka na vallidnostsj




	
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

			 get_names(buff, card_number);
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
	//char card_number[] = "1234567890123456"; //just random number
	char card_number[] =   "6799999900004646"; //just random number
	//char test_account_info[] = "400000000000;499999999999;VISA;"; //25 29

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


