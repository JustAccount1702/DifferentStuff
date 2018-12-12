#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "DifferentStuff.hpp"

unsigned menu(const std::string& input, HANDLE h)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	WORD initAttributes = csbiInfo.wAttributes;
	unsigned short choice = 0;
	std::vector<std::string> menuKeys = stringParser(input);
	while (true) {
		SetConsoleCursorPosition(h, { 0,0 });
		for (unsigned short i = 0; i < menuKeys.size(); i++)
			if (i == choice)
			{
				SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				std::cout << menuKeys[i] << std::endl;
				SetConsoleTextAttribute(h, initAttributes);
			}
			else std::cout << menuKeys[i] << std::endl;

		switch (_getch())
		{
		case 72:if (choice) choice--; break;
		case 80:if (choice < menuKeys.size() - 1) choice++; break;
		case 13: return choice;
		}

	}
	SetConsoleTextAttribute(h, initAttributes);
}

std::vector<std::string> stringParser(const std::string& input)
{
	std::string buff;
	std::vector<std::string> output;
	for (const char c : input)
		if (c == '\n')
		{
			output.push_back(buff);
			buff = "";
		}
		else buff += c;
	return output;
}
bool toUnsigned(std::string& input, unsigned& val)
{
	try
	{
		if (input.size() == 0) throw (-2);
		for (unsigned i = 0; i < input.size(); i++)
		{
			if (input[0] == '-') throw (-1);
			if (input[i] < '0' || input[i] > '9')
				throw (int)i;
		}

		val = atoi(input.c_str());
		return true;
	}
	catch (int ex)
	{
		if (ex == -1)
		{
			std::cerr << "Exception! Negative value" << std::endl;
			return false;
		}
		if (ex == -2)
		{
			std::cerr << "Exception! Input cannot be empty" << std::endl;
			return false;
		}
		else
		{
			std::cerr << "Exception! " << std::endl << input << std::endl << std::setw(ex + 1) << "|" << " - NaN value. Expected unsigned integer" << std::endl;
			val = 0;
			return false;
		}
	}
}

void centerAlign(std::string str)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD initialColorAttr;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	initialColorAttr = csbiInfo.wAttributes;

	size_t maxLen = csbiInfo.srWindow.Right;
	std::vector<int> stringFormatter;
	std::stringstream sstr(str);
	unsigned raws = 0;

	std::string line;
	std::vector<unsigned> wordsLength;
	unsigned it;
	while (getline(sstr, line))
	{
		it = 0;
		std::stringstream lineStream(line);
		std::string word;
		while (lineStream >> word)
		{
			if (it < wordsLength.size())
				wordsLength[it] = max(wordsLength[it], word.size());
			else
				wordsLength.push_back(word.size());
			++it;
		}
		raws = max(raws, it);
	}


	unsigned lineLength = std::accumulate(wordsLength.begin(), wordsLength.end(), 0);

	bool wideFormat = (maxLen >= (lineLength + 3 * wordsLength.size() + 1));

	stringFormatter.push_back(0);
	for (int wordLength : wordsLength)
	{
		stringFormatter.push_back(*(stringFormatter.end() - 1) + wordLength + 1 + ((wideFormat) ? 2 : 0));
	}


	for (size_t it = 0; it <= lineLength + ((wideFormat) ? 3 * raws : raws); ++it)
		if (find(stringFormatter.begin(), stringFormatter.end(), it) != stringFormatter.end())
			std::cout << '+';
		else
			std::cout << '-';
	std::cout << std::endl;

	sstr.clear();
	sstr.str(str);

	if (maxLen >= (lineLength + wordsLength.size() + 1))
	{
		while (getline(sstr, line))
		{
			it = 0;
			std::stringstream lineStream(line);
			std::string word;
			std::cout << '|';
			while (lineStream >> word)
			{
				int offset = wordsLength[it] - word.size();
				if (it)
					if (offset % 2)
						std::cout << std::setw(offset / 2 + ((wideFormat) ? 1 : 0)) << "" << word << std::setw(offset / 2 + 1 + ((wideFormat) ? 1 : 0)) << "" << '|';
					else
						std::cout << std::setw(offset / 2 + ((wideFormat) ? 1 : 0)) << "" << word << std::setw(offset / 2 + ((wideFormat) ? 1 : 0)) << "" << '|';
				else std::cout << std::setw((wideFormat) ? 1 : 0) << "" << word << std::setw(offset + ((wideFormat) ? 1 : 0)) << "" << '|';
				++it;

			}
			std::cout << std::endl;
			for (size_t it = 0; it <= lineLength + ((wideFormat) ? 3 * raws : raws); ++it)
				if (stringFormatter.end() != find(stringFormatter.begin(), stringFormatter.end(), it))
					std::cout << '+';
				else
					std::cout << '-';
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "Not enough space. Window is too small" << std::endl;
		return;
	}
}