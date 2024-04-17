#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int const marks = 4;
int const i_size = marks * 2 - 1;

void ask(const string& file_name) {
	ofstream file(file_name, ios::app);

    int digit;
	cout << "mark ... from 1 to 4: ";
	cin >> digit;
    file << digit << ' ';

    file.close();
}

void make_file(vector<int>& numbers, const string& file_name)
{
	ifstream file(file_name);
    int digit;

    numbers.reserve(52);
   	while (file >> digit)
    {
        numbers.push_back(digit - 1);
    }

    file.close();
}

void draw_plot(vector<vector<char> >& line, const int j_size, const vector<int>& numbers)
{
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

void view_plot(const vector<vector<char> >& line, const int j_size)
{
	cout << " ^" << endl;
	int u = marks + 1;
	for(int i = 0; i < i_size; i++)
	{
		i % 2 == 0 ? cout << --u : cout << ' ';
		cout << '|';
		for(int j = 0; j < j_size; j++)
			cout << line[i][j];
		cout << endl;
	}

	cout << ' '<< '\\';
	for(int j = 1; j < j_size + 2; j++)
		cout << '-';
	cout << '>'<< endl;
	for(int j = 1; j < j_size + 3; j++)
	{
		if((j + 2) % 5 != 0)
			cout << ' ';
		else
		{
			u > 9 ? j++ : j;
			cout << u++;
		}
	}
	cout << endl;
}

int main(){
	vector<int> numbers;
	string file_name = "/Users/timapashuk/Documents/lifeline/marks.txt";
	ask(file_name);
	make_file(numbers, file_name);

	int j_size = numbers.size() * 5 - 4;
	vector<vector<char> > line(i_size, vector<char>(j_size));



	draw_plot(line, j_size, numbers);
	view_plot(line, j_size);

	return 0;
}






