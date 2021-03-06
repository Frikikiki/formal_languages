#include "pch.h"
#include "toMealy.h"
#include "toMoore.h"


int main()
{
	int vertexCount, inSymbolsCount, outSymbolsCount;
	std::string machineType;
	GetParams(vertexCount, inSymbolsCount, outSymbolsCount, machineType);
	if (machineType == MOORE)
	{
		TransformMooreToMealy(vertexCount, inSymbolsCount, outSymbolsCount);
		return 0;
	}
	else if (machineType == MEALY)
	{
		TransformMealyToMoore(vertexCount, inSymbolsCount, outSymbolsCount);
		return 0;
	}
	else
	{
		return 1;
	}
}