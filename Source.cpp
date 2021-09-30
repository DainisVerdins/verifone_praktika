/*
//First of all make the programme then improve it by newest standart
*/

#include<iostream>//cout
#include<fstream>//ifstream
#include<string>//string
#include<sstream>//stringstream
#include<vector>
#include <cctype>//isdigit

#include <windows.h> //Sleep()
#include  <io.h>//acess

constexpr auto EXIT_SEQUENCE = "q";
constexpr auto CARD_NUM_LENGTH = 16;

//return users input as string
std::string get_user_input() {
	std::string input;
	std::cin >> input;
	return input;
}

bool is_exit_seq(const std::string& s) {
	return s == EXIT_SEQUENCE;
}

bool is_valid_card_num(const std::string& card_num) {

	if (card_num.length() != CARD_NUM_LENGTH)
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

std::string get_name_from_records(const std::string& file_name, const std::string& card_num);

bool auth_passed(const std::string& record, const std::string& card_num, std::string& card_name);

std::vector<std::string> tokenize(const std::string& record, const  char delimiter);

bool in_range(const std::string& low, const std::string& high, const std::string& target);

bool valid_sum(const std::string& sum);

bool write_record(const std::string& file_name, const std::string& user_card_number,
	const std::string& user_name, const std::string& user_sum);


int main() {
	//first input will be card number 
	//second sum
	std::string user_input{ "Hello C++ verifone" };
	const std::string input_file_name{ "file.txt" };
	const std::string output_file_name{ "trans.txt" };
	const int card_number_length = 16;
	
	while (true) {
		std::cout << "Enter precisly 16 digit big card number or 'q' for exit\n";
		std::cout << "****************\n";
		user_input = get_user_input();
		if (is_exit_seq(user_input))
		{
			return 0;
		}

		if (is_valid_card_num(user_input))
		{
			std::string name;

			name = get_name_from_records(input_file_name, user_input);
			if (name.empty())
			{
				//TODO make it in cxx style output
				fprintf(stderr, "inputted card number was not found in recordings. Try different one\n");
				Sleep(2000);// 2 seconds
			}
			else {
				while (true) {
					//some prompt
					printf("Enter the sum in format 'nnnn.mm' where:\n");
					printf("'nnnn' – 1 to 4 long sum in euros, \n");
					printf("'mm' – precisely 2 digits sum in cents. ,\n");
					printf("press 'q' and enter to exit.\n");
					std::string user_sum = get_user_input();
					if (valid_sum(user_sum))
					{
						// user input containts valid card number at this moment
						if (write_record(output_file_name, user_input, name, user_sum)) {
							std::cout << "added new record to db\n";
						}
						else {
							std::cout << "did not added record to db\n";
						}
						break;
					}
					else {
						std::cout << "inputed sum was bad one, try another\n";
					}
				}
			}

		}
		else {
			std::cout << "wrong card number length or not contains all digits\n";
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

//  splits record string into tokens+
//  checks if card_num is between values from record in manner [start;end]
//  writing card name into card name and return true;
bool auth_passed(const std::string& record, const std::string& card_num, std::string& card_name)
{


	const char record_delimeter = ';';
	auto tokens = tokenize(record, record_delimeter);


	//tokens and what they contain
	//tokens[0]- range start
	//tokens[1] - range end
	//tokens[2] - name
	if (in_range(tokens[0], tokens[1], card_num)) {
		card_name = tokens[2];
		return true;
	}
	else {
		return false;
	}

}

//  tokenizes inputed string by spliting records to tokens by delimeter
//  if wrong delimeter will return full record back in vector
std::vector<std::string> tokenize(const std::string& record, const  char delimiter)
{
	//TODO some max cap of tokens otherwise if data is corrupted overflow/

	std::vector <std::string> tokens;

	// stringstream class check1
	std::stringstream check1(record);

	std::string intermediate;

	// Tokenizing w.r.t. space ' '
	while (std::getline(check1, intermediate, delimiter))
	{
		tokens.push_back(intermediate);
	}
	return tokens;
}

bool in_range(const std::string& low, const std::string& high, const std::string& target)
{
	return target.compare(0, low.length(), low) >= 0
		&& target.compare(0, high.length(), high) <= 0;

}

// check if users inputed sum is correct
// by specific criteria
bool valid_sum(const std::string& sum)
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
	const char delimeter = '.';

	const int max_sum_length = max_n_count + m_count + 1;//+1 because delimeter
	const int min_sum_length = min_n_count + m_count + 1;

	if (sum.length() > max_sum_length || sum.length() < min_sum_length) {
		return false;
	}

	//check on delimeter pos
	std::size_t delimeter_pos = sum.find(delimeter);
	if (delimeter_pos == std::string::npos)//not found delimeter case
	{
		return false;
	}
	//multiple delimeters case
	if (delimeter_pos != sum.rfind(delimeter))
	{
		return false;
	}
	//case where delimeter is in wrong position
	//check if it is in -2 pos before last pos in str
	if (sum.at(sum.length() - m_count - 1) != delimeter)
	{
		return false;
	}

	for (size_t i = 0; i < sum.length(); i++)
	{
		if (!std::isdigit(sum.at(i)) && sum.at(i) != delimeter)
		{
			return false;
		}

	}


	return true;
}

// writing to a file record
// on succes return true otherwise false
// false in case file have write permission or cannot be created
bool write_record(const std::string& file_name, const std::string& user_card_number,
	const std::string& user_name, const std::string& user_sum)
{
	const char delimeter = ';';
	// Check for file existance.
	// Assume file is read-only.
	/* modes
	00	Existence only
	02	Write-only
	04	Read-only
	06	Read and write
	*/
	//-1 means true 
	if ((_access(file_name.c_str(), 0)) == -1) {

		std::ofstream ofs;
		ofs.open(file_name, std::ios::app);
		if (!ofs)
		{
			std::cout << "cannot create file\n";
			return false;
		}
		if (ofs.is_open())
		{
			ofs << user_card_number << delimeter
				<< user_name << delimeter
				<< user_sum << delimeter << '\n';

			ofs.close();
			return true;
		}
		else
		{
			std::cout << "Unable to open file'\n'";
			return false;
		}

	}
	else {
		// Check for write permission.
		// Assume file is read-only.
		/* modes
		00	Existence only
		02	Write-only
		04	Read-only
		06	Read and write
		*/
		//-1 means true 
		if ((_access(file_name.c_str(), 2)) == -1) {
			std::cout << "File " << file_name << " does not have write permission.\n";
			return false;
		}


		std::ofstream ofs{ file_name,std::ios::out | std::ios::app };
		if (!ofs)
		{
			std::cout << "cannot create file\n";
			return false;
		}
		if (ofs.is_open())
		{
			ofs << user_card_number << delimeter
				<< user_name << delimeter
				<< user_sum << delimeter << '\n';

			ofs.close();
			return true;
		}
		else
		{
			std::cout << "Unable to open file'\n'";
			return false;
		}

	}


}


