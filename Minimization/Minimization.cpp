#include "pch.h"
#include "moore.h"
#include "mealy.h"


int main()
{
	int statesCount, inSymbolsCount, outSymboldCount;
	std::string machineType;
	GetParams(statesCount, inSymbolsCount, outSymboldCount, machineType);
	if (machineType == MEALY)
	{
		MinimizeMealy(statesCount, inSymbolsCount);
	}
	else if (machineType == MOORE)
	{
		MinimizeMoore(statesCount, inSymbolsCount);
	}
	else
	{
		return 1;
	}
}
