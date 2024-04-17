#include <iostream>
#include <fstream>
#include <vector>
#include <string> 


const int marks = 4;
const int i_size = marks * 2 - 1;

void ask(const std::string& file_name) {
    std::ofstream file(file_name, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    int digit;
    std::cout << "Enter a mark from 1 to 4: ";
    std::cin >> digit;
    if (digit < 1 || digit > 4) {
        std::cerr << "Invalid input. Please enter a number between 1 and 4." << std::endl;
        return;
    }
    file << digit << ' ';
    file.close();
}

void make_file(std::vector<int>& numbers, const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    int digit;
    while (file >> digit) {
        numbers.push_back(digit - 1);
    }
    file.close();
}

void draw_plot(std::vector<std::vector<char> >& line, const int j_size, const std::vector<int>& numbers) {
    int index = 0;

	for(int i = 0; i < i_size; i++)
	{
		for(int j = 0; j < j_size; j++)
		{
			line[i][j] = ' ';
		}
	}

	int number = 2 * (3 - numbers[index++]);
	line[number][0] = '!';
	int previous_number = number;	
	for(int j = 5; j < j_size; j += 5)
	{
		int number = 2 * (3 - numbers[index++]);
		line[number][j] = '!';
		int i = 0;
		for(int u = j - 4; u < j; u++)
		{
			i++;
			if(number - previous_number == 0)
			{
				line[previous_number][u] = '*';
			} else if((number - previous_number) == 2)
			{
				line[previous_number + (i - 1)/2 + 1][u] = '*';
			} else if((number - previous_number) == -2)
			{
				line[previous_number - (i - 1)/2 - 1][u] = '*';
			} else if((number - previous_number) == 4)
			{
				line[previous_number + i][u] = '*';
			} else if((number - previous_number) == -4)
			{
				line[previous_number - i][u] = '*';
			} else if((number - previous_number) == 6)
			{
				line[previous_number + i + i / 2][u] = '*';
				line[previous_number + i + + i / 2 + i % 2][u] = '*';
			} else if((number - previous_number) == -6)
			{
				line[previous_number - i - i / 2][u] = '*';
				line[previous_number - i - i / 2 - i % 2][u] = '*';
			}
		}
		previous_number = number;
	}
}

void view_plot(const std::vector<std::vector<char> >& line, const int j_size) {
	std::cout << " ^" << std::endl;
	int u = marks + 1;
	for(int i = 0; i < i_size; i++)
	{
		i % 2 == 0 ? std::cout << --u : std::cout << ' ';
		std::cout << '|';
		for(int j = 0; j < j_size; j++)
			std::cout << line[i][j];
		std::cout << std::endl;
	}

	std::cout << ' '<< '\\';
	for(int j = 1; j < j_size + 2; j++)
		std::cout << '-';
	std::cout << '>'<< std::endl;
	for(int j = 1; j < j_size + 3; j++)
	{
		if((j + 2) % 5 != 0)
			std::cout << ' ';
		else
		{
			u > 9 ? j++ : j;
			std::cout << u++;
		}
	}
	std::cout << std::endl;
}

int main() {
    std::vector<int> numbers;
    std::string file_name = "marks.txt";

    ask(file_name);
    make_file(numbers, file_name);

    int j_size = numbers.size() * 5 - 4;
    std::vector<std::vector<char> > line(i_size, std::vector<char>(j_size));

    draw_plot(line, j_size, numbers);
    view_plot(line, j_size);

    return 0;
}