#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <map>
#include <set>

using Matrix = std::vector<std::vector<std::string>>;
using MatrixMap = std::map<std::string, std::vector<std::string>>;

void GetParams(int &inSymbolsCount, int &outSymbolsCount)
{
	std::cin >> inSymbolsCount;
	std::cin >> outSymbolsCount;
}

void PrintMatrix(const Matrix &matrix)
{
	for (const auto i : matrix)
	{
		for (int j = 0; j < i.size(); j++)
		{
			std::cout << "q" + i[j];
			if (j < i.size() - 1)
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

std::string GetIndex(std::string str)
{
	std::string result = "";
	std::regex digits("\\d");
	std::sregex_token_iterator iter(str.begin(), str.end(), digits);

	for (std::sregex_token_iterator end; iter != end; ++iter)
	{
		result += iter->str();
	}

	return result;
}

Matrix GetTransposedMatrix(const Matrix &matrix)
{
	int matrixRowsCount = matrix.size();
	int matrixColumnsCount = matrix[0].size();

	Matrix transposedMatrix(matrixColumnsCount, std::vector<std::string>(matrixRowsCount));

	for (int i = 0; i < matrixRowsCount; i++)
	{
		for (int j = 0; j < matrixColumnsCount; j++)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}
	return transposedMatrix;
}

Matrix GetMatrix(int i, int j)
{
	Matrix matrix;
	std::vector<std::string> vec;
	std::string str;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			std::cin >> str;
			vec.push_back(GetIndex(str));
		}
		matrix.push_back(vec);
		vec.clear();
	}
	return matrix;
}

MatrixMap GetMatrixMap(const Matrix &matrix)
{
	MatrixMap result;
	for (int i = 0; i < matrix.size(); i++)
	{
		result.insert({ std::to_string(i), matrix[i] });
	}
	return result;
}

void AddStrings(std::string &left, std::string right)
{
	left += right;
	std::set<char> chars;

	left.erase(
		std::remove_if(
			left.begin(),
			left.end(),
			[&chars](char i) {
		if (chars.count(i)) { return true; }

		chars.insert(i);
		return false;
	}
		),
		left.end()
		);
	std::sort(left.begin(), left.end());
}

std::vector<std::string> GetNewStatesVector(MatrixMap matrixMap, std::string state)
{
	int vecSize = matrixMap.begin()->second.size();
	std::vector<std::string> result;
	for (int i = 0; i < vecSize; i++)
	{
		std::string str = "";
		for (char ch : state)
		{
			MatrixMap::iterator it = matrixMap.find(std::string(1, ch));
			AddStrings(str, it->second[i]);
		}
		result.push_back(str);
	}
	return result;
}

Matrix GetResultMatrix(MatrixMap matrixMap)
{
	Matrix result;
	for (auto &i : matrixMap)
	{
		result.push_back(i.second);
	}
	return GetTransposedMatrix(result);
}

void FillMatrixMap(MatrixMap &matrixMap)
{
	for (auto i : matrixMap)
	{
		for (auto &j : i.second)
		{
			MatrixMap::iterator it = matrixMap.find(j);
			if (it == matrixMap.end())
			{
				matrixMap.insert({ j, GetNewStatesVector(matrixMap, j)});
			}
		}
	}
}

void Determinate(int inSymbolsCount, int outSymboldCount)
{
	Matrix matrix = GetMatrix(inSymbolsCount, outSymboldCount);
	matrix = GetTransposedMatrix(matrix);
	MatrixMap matrixMap = GetMatrixMap(matrix);
	FillMatrixMap(matrixMap);
	PrintMatrix(GetResultMatrix(matrixMap));
}


int main()
{
	int inSymbolsCount, outSymboldCount;
	GetParams(inSymbolsCount, outSymboldCount);
	Determinate(inSymbolsCount, outSymboldCount);
}

