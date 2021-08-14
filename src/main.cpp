#include<cstdio>
#include <cstring>//pause



bool get_name();

//searches card number in files data
//if found returns true and Name of card user
//otherwise false
bool search_card_num(char file_name[],char card_number[]) {

	FILE* pfile;
	const size_t buff_size = 255;

	char buff[buff_size];

	char* pch;

	fopen_s(&pfile, file_name, "rt");

	if (pfile != NULL) {
		while (fgets(buff, buff_size, pfile) != NULL) {
			printf("%s", buff);

			pch = strchr(buff, ';');
			while (pch!=NULL)
			{
				printf("%c ", *pch);
				printf("found at %d\n", pch - buff + 1);
				pch = strchr(pch + 1, ';');
			}
			printf("\n");
		}

		fclose(pfile);
		return true;

	}
	else
	{
		printf("cannot find file \"%s\"", file_name);
		return false;
	}

}


int main() {
	printf("Hello World!\n");
	char file_name[] = "file.txt";
	char card_number[16] = "1564683215646"; //just random number
	char card_number1[16] = "50000001"; //just random number
	char card_number2[16] = "4000"; //just random number
	search_card_num(file_name, card_number);


	return 0;
}
