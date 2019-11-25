#include "pch.h"
#include "toMealy.h"


std::vector<std::string> GetOutputFunction(int size)
{
	std::vector<std::string> outputFunction(size);
	for (int i = 0; i < size; i++)
	{
		std::cin >> outputFunction[i];
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


void MakeGraphDot(const Matrix &matrix, const std::vector<std::string> &outputFunction)
{
	std::ofstream outputFile(DOT_FILE_NAME);
	outputFile << DIGRAPH_PART << std::endl;
	for (int i = 0; i < matrix[0].size(); i++)
	{
		outputFile << TO_MEALY_STATE_NAME_MEALY << i << SEMICOLON << std::endl;
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			outputFile << TO_MEALY_STATE_NAME_MEALY << j << ARROW << TO_MEALY_STATE_NAME_MEALY << matrix[i][j];
			outputFile << LABEL_PART << i;
			outputFile << outputFunction[matrix[i][j]];
			outputFile << CLOSING_BRACKET << SEMICOLON << std::endl;
		}
	}
	outputFile << CLOSING_BRACE;
}


void TransformMooreToMealy(int vertexCount, int inSymbolsCount, int outSymbolsCount)
{
	std::vector<std::string> outputFunction = GetOutputFunction(vertexCount);
	Matrix matrix = GetMatrix(inSymbolsCount, vertexCount);
	for (int i = 0; i < inSymbolsCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			std::cout << TO_MEALY_STATE_NAME_MEALY << matrix[i][j] << outputFunction[matrix[i][j]];
			if (j < vertexCount - 1)
			{
				std::cout << SPACE;
			}
		}
		std::cout << std::endl;
	}
	MakeGraphDot(matrix, outputFunction);
}