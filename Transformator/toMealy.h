#pragma once
#include "common.h"

const std::string TO_MEALY_STATE_NAME_MEALY = "q";


std::vector<std::string> GetOutputFunction(int size);

Matrix GetMatrix(int i, int j);

void MakeGraphDot(const Matrix &matrix, const std::vector<std::string> &outputFunction);

void TransformMooreToMealy(int vertexCount, int inSymbolsCount, int outSymbolsCount);