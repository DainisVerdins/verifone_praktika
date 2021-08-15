#include<stdio.h>
#include <cstring>//pause
#include <cctype>//isdigit



char* get_names(char* str, char* card_number)
{

	char range_start[16];
	char range_end[16];

	const size_t buff_size = 255;
	char buff[buff_size];//buffer what contains name;


	char* pch;
	pch = strchr(str, ';'); //TODO: make separator sign as macros
	while (pch != NULL)
	{
		printf("%c ", *pch);
		printf("found at %lld\n", pch - str + 1);
		pch = strchr(pch + 1, ';');
	}
	printf("\n");
	char dummy[] = "Wow!";
	return card_number;
}





//searches card number in files data
//if found returns true and Name of card user
//otherwise false
char* get_name(const char file_name[], char card_number[])
{

	FILE* pfile;
	char* Name;
	const size_t buff_size = 255;
	Name = NULL;
	char buff[255];


	fopen_s(&pfile, file_name, "rt");

	if (pfile == NULL) {

		printf("cannot find file \"%s\"", file_name);
		return NULL;
	}
	else {

		while (fgets(buff, buff_size, pfile) != NULL) {
			printf("%s", buff);

			Name = get_names(buff, card_number);
		}

		fclose(pfile);
		return Name;
	}

}

//check if card_number have valid specifics 
bool is_valid(const char card_number[])
{
	int card_length = strlen(card_number);
	int i = 0;

	//card number must precisly 16 digits
	const int chars_in_card = 16;//probably to need to add as macros

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

	if (is_valid(card_number))
	{
		puts(card_number);

	}
	else {
		printf("bad cards number -> %s\n", card_number);
	}


	return 0;
}
