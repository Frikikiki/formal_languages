#pragma once
#include "minCommon.h"

void FillMatrices(Matrix &matrix, Matrix &outputFunction);

void MinimizeMealy(int statesCount, int inSymbolsCount);

std::vector<int> GetOutputFunction(const Matrix &matrix);