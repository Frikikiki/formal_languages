#pragma once
#include "minCommon.h"


std::vector<int> GetOutputFunction(int size);

Matrix GetMatrix(int i, int j);

void MinimizeMoore(int statesCount, int inSymbolsCount);
