#include "pch.h"
#include "moore.h"



std::vector<int> GetOutputFunction(int size)
{
	std::vector<int> outputFunction(size);
	for (int i = 0; i < size; i++)
	{
		std::string str;
		std::cin >> str;
		outputFunction[i] = GetIndex(str);
	}
	return outputFunction;
}


Matrix GetMatrix(int i, int j)
{
	Matrix matrix;
	std::vector<int> vec;
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

void MinimizeMoore(int statesCount, int inSymbolsCount)
{
	std::vector<int> outputFunction = GetOutputFunction(statesCount);
	Matrix statesMatrix = GetMatrix(inSymbolsCount, statesCount);
	EqClasses fisrtEqClasses = GetFirstEqClasses(statesMatrix, outputFunction);
	PrintMatrix(GetMatrix(GetMinimizedClasses(fisrtEqClasses, statesMatrix)));
}