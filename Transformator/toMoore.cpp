#include "pch.h"
#include "toMoore.h"


MooreState::MooreState(int stateIndex, int outSymbolIndex)
{
	this->stateIndex = stateIndex;
	this->outSymbolIndex = outSymbolIndex;
}


bool Compare(const MooreState &left, const MooreState &right)
{
	if (left.stateIndex != right.stateIndex)
	{
		return left.stateIndex < right.stateIndex;
	}
	else
	{
		return left.outSymbolIndex < right.outSymbolIndex;
	}
}


std::vector<MooreState> GetMooreStates(StringMatrix &matrix)
{
	std::vector<MooreState> result;
	std::string str;
	std::set<std::string> strSet;
	bool isNumber = false;
	int statesCount = 0;

	while (!std::cin.eof())
	{
		std::cin >> str;
		matrix[statesCount / matrix[0].size()][statesCount % matrix[0].size()] = str;
		statesCount++;
		isNumber = false;
		for (int i = 0; i < str.size(); i++)
		{
			if (isdigit(str[i]))
			{
				isNumber = true;
			}
			else if (isNumber)
			{
				
				if (strSet.count(str) == 0)
				{
					result.emplace_back(GetIndex(str.substr(0, i)),
										GetIndex(str.substr(i)));
					strSet.insert(str);
				}
				break;
			}
		}
	}
	return result;
}


void MakeGraphDot(const Matrix &matrix, const std::vector<MooreState> &mooreStates)
{
	std::ofstream outputFile(DOT_FILE_NAME);
	outputFile << DIGRAPH_PART << std::endl;
	for (int i = 0; i < mooreStates.size(); i++)
	{
		outputFile << TO_MOORE_STATE_NAME_MOORE << i << TO_MOORE_OUT_SYMBOL_NAME << 
							mooreStates[i].outSymbolIndex << SEMICOLON << std::endl;
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			outputFile << TO_MOORE_STATE_NAME_MOORE << j << TO_MOORE_OUT_SYMBOL_NAME << mooreStates[j].outSymbolIndex << ARROW;
			outputFile << TO_MOORE_STATE_NAME_MOORE << matrix[i][j] << mooreStates[matrix[i][j]].outSymbolIndex;
			outputFile << LABEL_PART << i << CLOSING_BRACKET << SEMICOLON << std::endl;
		}
	}
	outputFile << CLOSING_BRACE;
}

int GetIndexMoore(const std::vector<MooreState> &mooreStates, std::string str)
{
	for (int i = 0; i < mooreStates.size(); i++)
	{
		if (TO_MOORE_STATE_NAME_MEALY + std::to_string(mooreStates[i].stateIndex) + 
			TO_MOORE_OUT_SYMBOL_NAME + std::to_string(mooreStates[i].outSymbolIndex) == str)
		{
			return i;
		}
	}
	return -1;
}

void TransformMealyToMoore(int vertexCount, int inSymbolsCount, int outSymbolsCount)
{
	StringMatrix matrix(inSymbolsCount, std::vector<std::string>(vertexCount));
	std::vector<MooreState> mooreStates = GetMooreStates(matrix);
	std::sort(mooreStates.begin(), mooreStates.end(), Compare);
	Matrix resultMatrix(inSymbolsCount, std::vector<int>(mooreStates.size()));
	for (int i = 0; i < inSymbolsCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			for (int k = 0; k < mooreStates.size(); k++)
			{
				if (mooreStates[k].stateIndex == j)
				{
					resultMatrix[i][k] = GetIndexMoore(mooreStates, matrix[i][j]);
					std::cout << TO_MOORE_STATE_NAME_MOORE << GetIndexMoore(mooreStates, matrix[i][j]);
					if (k < mooreStates.size() - 1)
					{
						std::cout << SPACE;
					}
				}
			}
		}
		if (i < matrix.size() - 1)
		{
			std::cout << std::endl;
		}
	}
	
	MakeGraphDot(resultMatrix, mooreStates);
}