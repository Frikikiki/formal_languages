#pragma once
#include <iostream>
#include <vector>
#include <regex>

const std::string SPACE = " ";
const std::string MEALY = "mealy";
const std::string MOORE = "moore";

using Matrix = std::vector<std::vector<int>>;


void GetParams(int &statesCount, int &inSymbolsCount,
	int &outSymbolsCount, std::string &machineType);

int GetIndex(std::string str);

Matrix GetTransposedMatrix(const Matrix &matrix);

void PrintMatrix(const Matrix &matrix);