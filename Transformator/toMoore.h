#pragma once
#include "common.h"
#include <set>

const std::string TO_MOORE_STATE_NAME_MOORE = "z";
const std::string TO_MOORE_STATE_NAME_MEALY = "s";
const std::string TO_MOORE_OUT_SYMBOL_NAME = "y";


struct MooreState
{
	int stateIndex;
	int outSymbolIndex;

	MooreState(int stateIndex, int outSymbolIndex);
};


bool Compare(const MooreState &left, const MooreState &right);

std::vector<MooreState> GetMooreStates(StringMatrix &matrix);

int GetIndexMoore(const std::vector<MooreState> &mooreStates, std::string str);

void MakeGraphDot(const Matrix &matrix, const std::vector<MooreState> &mooreStates);

void TransformMealyToMoore(int vertexCount, int inSymbolsCount, int outSymbolsCount);