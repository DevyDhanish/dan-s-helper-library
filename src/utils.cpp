#include "../include/utils/utils.hpp"
#include "../include/debug/debug.hpp"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

const char alphabets[26 + 26 + 1] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char numbers[11] = "0123456789";

const char symbols[35 + 1] = "`!@#$%^&*()_+|}{\":<>?~-=[]\\;',./";

const char allChars[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`!@#$%^&*()_+|}{\":<>?~-=[]\\;',./ \n\r\t\0";

void __print__errorlog_background_banner__(const char *text, unsigned short foregroundColor, unsigned short backgroundColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, foregroundColor | backgroundColor);
	std::cout << text;
	SetConsoleTextAttribute(hConsole, WHITE_COLOR);
	std::cout << "] : ";
}

void __print__banner(CONSOLELOG::LOGTYPE type)
{
	switch (type)
	{
	case 0:
	{
		__print__errorlog_background_banner__("ERROR", WHITE_COLOR, ERROR_BG_COLOR | FOREGROUND_INTENSITY);
		break;
	}
	case 1:
	{
		__print__errorlog_background_banner__("INFO", WHITE_COLOR, INFO_BG_COLOR | FOREGROUND_INTENSITY);
		break;
	}
	case 2:
	{
		__print__errorlog_background_banner__("DEBUG", WHITE_COLOR, DEBUG_BG_COLOR | FOREGROUND_INTENSITY);
		break;
	}
	default:
	{
		std::cout << "Invalid Type provided\n";
		break;
	}
   }
}

std::vector<std::string> splitIntoVector(const char *str, char point, uint32_t size)
{
	std::vector<std::string> output;
	std::string word = "";

	uint32_t i = 0;
	while(i <= size)		// using `<=` because then it will go upto the end of the input `adfasdfadsfsd;` every input should end with `;`.
	{
		if(str[i] == point)
		{
			output.push_back(word);
			word = "";
		}
		else
		{
			word += str[i];
		}

		i++;
	}

	return output;
}