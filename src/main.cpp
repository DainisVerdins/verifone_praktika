#include<stdio.h>
#include <cstring>//pause
#include <cctype>//isdigit


#define STR_BUFFER_SIZE 255


struct CardInfo{
	//TODO make then ass arrays of specific size not as pointers
	 char* name;
	 char* range_start;
	 char* range_end;
};

void parse_name( const char* str, CardInfo &card)
{
	const size_t range_size = 16;
	char range_start[range_size] = {};
	char range_end[range_size] = {};

	const size_t name_size = 255;
	char card_name[name_size] = {};//buffer what contains name;

	sscanf_s( str, "%[0-9];%[0-9];%[a-zA-Z];", range_start, range_size, range_end, range_size, card_name, name_size); //parsing data of string

	puts(range_start);
	puts(range_end);
	puts(card_name);
	
}

char* get_names(const char* str, char* card_number)
{

	CardInfo card;
	parse_name(str, card);
	printf("card info \n");
	puts(card.range_start);
	puts(card.range_end);
	puts(card.name);
	printf("end of info\n");
	


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


