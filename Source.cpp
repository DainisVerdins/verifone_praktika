#include<iostream>
#include<fstream>
#include<string>
#include <cctype>//isdigit
#include <windows.h> //Sleep()

constexpr auto EXIT_SEQUENCE = "q";

//return users input as string
std::string get_user_input() {
	std::string input = "1234567890123456";
	//std::cin >> input;
	return input;
}

bool is_exit_seq(const std::string& s) {
	return s == EXIT_SEQUENCE;
}

bool is_valid_card_num(const std::string& card_num, const int card_num_length) {

	if (card_num.length() != card_num_length)
	{
		return false;
	}

	//TODO need to make tests on for_each() with lambda
	for (auto& ch : card_num) {

		if (!std::isdigit(ch))
		{
			return false;
		}
	}



	return true;
}

//if card num found in recording then returns it name;
std::string get_name_from_records(const std::string& file_name, const std::string& card_num);

bool auth_passed(const std::string& record, const std::string& card_num, std::string& card_name);

int main() {
	//first input will be card number 
	//second sum
	std::string user_input{ "Hello C++ verifone" };
	const std::string input_file_name{ "file.txt" };
	const int card_number_length = 16;

	user_input = get_user_input();
	if (is_exit_seq(user_input))
	{
		std::cout << EXIT_SEQUENCE << std::endl;
	}
	else
	{
		if (is_valid_card_num(user_input, card_number_length))
		{
			std::string name;

			name = get_name_from_records(input_file_name, user_input);
			if (name.empty())
			{
				fprintf(stderr, "inputted card number was not found in recordings. Try different one\n");
				Sleep(2000);// 2 seconds
			}

			std::cout << user_input << std::endl;
		}

	}

	return 0;
}

//  reads data from file if contains card_num 
//  between [start:end] sequences in file 
//  returns name of the card, otherwise empty string
std::string get_name_from_records(const std::string& file_name, const std::string& card_num)
{
	std::string name;
	std::ifstream records{ file_name };
	if (!records)
	{
		//TODO make it c++ output not c-style one
		fprintf(stderr, "cannot find file \"%s\"\n", file_name.c_str());
		return name;
	}
	else {
		if (records.is_open())
		{
			std::string record_line;
			while (std::getline(records, record_line))
			{
				if (auth_passed(record_line, card_num, name))
				{
					break;
				}
			}
			records.close();
		}

	}
	return name;
}

//  checks if car_num is between of sequences of numbers in record
//  if found returns true and by reference name of card
bool auth_passed(const std::string& record, const std::string& card_num, std::string& card_name)
{
	//something to split record
	//something to check if card_num is between values [start;end]
	//write card name into card name and return true;
	return false;
}
