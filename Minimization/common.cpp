#include "pch.h"
#include "common.h"


void GetParams(int &statesCount, int &inSymbolsCount,
	int &outSymbolsCount, std::string &machineType)
{
	std::cin >> inSymbolsCount;
	std::cin >> outSymbolsCount;
	std::cin >> statesCount;
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

Matrix GetTransposedMatrix(const Matrix &matrix)
{
	int matrixRowsCount = matrix.size();
	int matrixColumnsCount = matrix[0].size();

	Matrix transposedMatrix(matrixColumnsCount, std::vector<int>(matrixRowsCount));

	for (int i = 0; i < matrixRowsCount; i++)
	{
		for (int j = 0; j < matrixColumnsCount; j++)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}
	return transposedMatrix;
}

void PrintMatrix(const Matrix &matrix)//TODO: универсализировать (разные буквы)?
{
	for (const auto i : matrix)
	{
		for (int j = 0; j < i.size(); j++)
		{
			std::cout << i[j];
			if (j < i.size() - 1)
			{
				std::cout << SPACE;
			}
		}
		std::cout << std::endl;
	}
}