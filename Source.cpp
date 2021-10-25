/*
//First of all make the programme then improve it by newest standart
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;
// 1 stands for ladder
// 2 stands for user
// 0 for empty space
//first occurence in floor if not found -1
int find_space(const vector<int>& floor, int parking_space);

std::string move_direction(int from, int to);

int ladders_depth(const vector<vector<int>>& carpark, int start_level, int pos);

vector<string> escape(const vector<vector<int>>& carpark)
{
	vector<string> output;

	// 1.find start pos of user in floor +
	// 2.find ladder in floor +
	// 3.calc distance between user and ladder +
	// 4.get result of witch dir user must move +
	// 5.return direction and distance as string +
	// 6.set users pos as one level above first floor
	// 7.find if any stairs if yes repeat from 3. statements
	// if not it means what we are in last floor and need to find exit
	// exit is far rigth element of last floor
	// 8, calc distance if have to exit
	// 9.get string of movement
	// 10.return vector of movements
	// .

	int prev_ladder_pos = find_space(carpark[0], 2);//find player
	int ladder_pos = find_space(carpark[0], 1);//find first ladder
	cout << move_direction(prev_ladder_pos, ladder_pos);//get distance 
	int depth = ladders_depth(carpark, 0, ladder_pos);
	cout << "D" + std::to_string(depth);//goo deep 

	for (size_t i = depth; i < carpark.size() - 1; i++)//from 1 because 0 floor was seen 
												 //-1 because diferent logick on check last floor 
	{
		prev_ladder_pos = ladder_pos;
		ladder_pos = find_space(carpark[i], 1);
		cout << move_direction(prev_ladder_pos, ladder_pos);

		depth = ladders_depth(carpark, i, ladder_pos);
		cout << " D" + std::to_string(depth);//goo deep 

		if (depth > 1)
		{
			i += depth;
		}
	}
	//last floor
	cout << move_direction(ladder_pos, 4);//far rigth most zeros position

	return output; // Code here
}

int main() {

	vector<vector<int>>floors{ {0, 2, 0, 0, 1},
							   {0, 0, 0, 0, 1},
							   {0, 0, 0, 0, 1},
							 {0, 0, 0, 0, 0} };
	auto output = escape(floors);

	for (size_t i = 0; i < output.size(); i++)
	{
		std::cout << output[i] << '\n';
	}
	std::cout << output.size() << '\n';
	return 0;
}

int find_space(const vector<int>& floor, int parking_space)
{
	for (size_t i = 0; i < floor.size(); i++)
	{
		if (parking_space == floor[i])
		{
			return i;
		}
	}
	return -1;//not found
}

std::string move_direction(int from, int to)
{
	const unsigned int distance = std::abs(from - to);
	//move to left
	if (from > to)
	{
		return "L" + std::to_string(distance);
	}
	else if (from < to)//move to rigth
	{
		return "R" + std::to_string(distance);
	}
	else {
		return "";
	}
}

int ladders_depth(const vector<vector<int>>& carpark, int start_level, int pos)
{
	int depth = 0;
	for (size_t i = start_level; i < carpark.size(); i++)
	{
		if (carpark[i][pos] == 1) {
			++depth;
		}
		else {
			return depth;
		}
	}
	return depth;
}




