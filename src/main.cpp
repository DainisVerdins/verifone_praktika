#include<stdio.h>
#include <cstring>//pause
#include <cctype>//isdigit
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
#define STR_BUFFER_SIZE 255


struct CardInfo {

	char name[255] = {};
	//ranges are from 1 to 16 digits
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


// Returns true if target in range [low..high], else false
//assumed what inputs are strings with \0
bool in_range(const char *low,const char * high, const char * target) {
	//probably need to use strncmp, to avoid error if string do not contain \n
	return strcmp(target, low) >= 0 && strcmp(target, high) <= 0;
}

//parses  auth_str into strings and puts data into CardInfo struct
void parse_card_info(const char* auth_str,CardInfo &card)
{
	//Range_Start;Range_End;Name; - format of inputed string

	sscanf_s(auth_str, "%[0-9];%[0-9];%[a-zA-Z];", card.range_start, card.get_range_size(),
												   card.range_end, card.get_range_size(),
												   card.name, card.get_name_size());
}

//check if card_number is valid for aut_str
//means auth_str contains ranges if card number is between ranges
//then is passed. 
//auth_str contains data to "apply" card number
bool is_auth_passed(const char* auth_str, const char* card_number)
{
	
	int i;
	CardInfo card;
	
	parse_card_info(auth_str, card);
	

	puts("\n");

	if (in_range(card.range_start,card.range_end,card_number))
	{
		printf("match\n");
			puts(card.range_start);
			puts(card_number);
			puts(card.range_end);
			puts(card.name);
			return true;
	}
	return false;
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

			 is_auth_passed(buff, card_number);
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
	char card_number[] =   "4799999900004646"; //just random number

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


