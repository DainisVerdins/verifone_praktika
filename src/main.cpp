#include<cstdio>
#include <cstring>//pause



const char* get_names( char* str,  char* card_number) {
	char* pch;
	pch =  strchr(str, ';');
	while (pch != NULL)
	{
		printf("%c ", *pch);
		printf("found at %lld\n", pch - str + 1);
		pch = strchr(pch + 1, ';');
	}
	printf("\n");

	return NULL;
}





//searches card number in files data
//if found returns true and Name of card user
//otherwise false
bool get_name(const char file_name[],  char card_number[]) {

	FILE* pfile;
	const size_t buff_size = 255;
	char buff[buff_size];


	fopen_s(&pfile, file_name, "rt");

	if (pfile == NULL) {

		printf("cannot find file \"%s\"", file_name);
		return false;
	}
	else{

		while (fgets(buff, buff_size, pfile) != NULL) {
			printf("%s", buff);

			printf("%s", get_names(buff, card_number));
		}

		fclose(pfile);
		return true;
	}

}


int main() {
	printf("Hello World!\n");
	char file_name[] = "file.txt";
	char card_number[16] = "1564683215646"; //just random number
	char card_number1[16] = "50000001"; //just random number
	char card_number2[16] = "4000"; //just random number
	get_name(file_name, card_number);


	return 0;
}
