#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> stringParser(string&);
int main()
{
	unsigned short choice = 0;
		while (true) {
			string menu =  R"(1. Add attestation from file
2. Show all student's marks
3. Show total amount of student's marks
4. Show all poor students
5. Show all GPA
0. Exit
)";
			vector<string> menuKeys = stringParser(menu);
			for (unsigned short i = 0; i < menuKeys.size(); i++)
				if (i == choice) 
					cout << "[[1;31mIn color" << endl;
				else cout << menuKeys[i] << endl;
			switch (_getch())//224 - keyboard?
			{
			case 77: std::cout << "Right" << std::endl; break;
			case 72: std::cout << "Up" << std::endl; if (choice) choice--; break;
			case 75: std::cout << "Left" << std::endl; break;
			case 80: std::cout << "Down" << std::endl; if (choice < menuKeys.size() - 1) choice++; break;
			}
		}
		return 0;
}

vector<string> stringParser(string& input)
{
	string buff;
	vector<string> output;
	for (const char c : input) 
		if (c == '\n')
		{
			output.push_back(buff);
			buff = "";
		}
		else buff += c;
	return output;
}