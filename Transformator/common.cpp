#include "pch.h"
#include "common.h"


void GetParams(int &vertexCount, int &inSymbolsCount,
	int &outSymbolsCount, std::string &machineType)
{
	std::cin >> inSymbolsCount;
	std::cin >> outSymbolsCount;
	std::cin >> vertexCount;
	std::cin >> machineType;
}


int GetIndex(std::string str)
{
	std::string result = "";
	std::regex digits("\\d");
	std::sregex_token_iterator iter(str.begin(), str.end(), digits);

	for (std::sregex_token_iterator end; iter != end; ++iter)
	{
		result += iter->str();
	}
	
	return std::stoi(result);
}