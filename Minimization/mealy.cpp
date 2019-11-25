#include "pch.h"
#include "mealy.h"

void FillMatrices(Matrix &matrix, Matrix &outputFunction)
{
	std::string str;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			std::cin >> str;
			bool isNumber = false;
			for (int k = 0; k < str.size(); k++)
			{
				if (isdigit(str[k]))
				{
					isNumber = true;
				}
				else if (isNumber)
				{
					matrix[i][j] = GetIndex(str.substr(0, k));
					outputFunction[i][j] = GetIndex(str.substr(k));
					break;
				}
			}
		}
	}
}

std::vector<int> GetOutputFunction(const Matrix &matrix)
{
	std::vector<int> result;
	std::map<std::vector<int>, int> columnAndClass;
	int classNumber = 1;
	for (const std::vector<int> &numbers: matrix)
	{
		std::map<std::vector<int>, int>::iterator it = columnAndClass.find(numbers);
		if (it == columnAndClass.end())
		{
			columnAndClass.insert({ numbers, classNumber });
			result.push_back(classNumber);
			classNumber++;
		}
		else
		{
			result.push_back(it->second);
		}
	}
	return result;
}

void MinimizeMealy(int statesCount, int inSymbolsCount)
{
	Matrix statesMatrix(inSymbolsCount, std::vector<int>(statesCount));
	Matrix outputMatrix(inSymbolsCount, std::vector<int>(statesCount));
	FillMatrices(statesMatrix, outputMatrix);
	std::vector<int> outputFunction = GetOutputFunction(GetTransposedMatrix(outputMatrix));
	EqClasses firstEqClasses = GetFirstEqClasses(statesMatrix, outputFunction);
	PrintMatrix(GetMatrix(GetMinimizedClasses(firstEqClasses, statesMatrix)));
}