#pragma once
#include <map>
#include "common.h"


struct Column
{
	int state;
	std::vector<int> classesNumbers;

	Column(int state, std::vector<int> classesNumbers);
};


struct EqClass
{
	int classNumber;
	mutable std::vector<Column> columns;
	std::vector<int> eqReason;

	EqClass(int classNumber, const std::vector<Column> &columns, const std::vector<int> &eqReason);
};


using EqClasses = std::vector<EqClass>;
using IntsMap = std::map<int, int>;


bool operator!=(const std::vector<Column> &left, const std::vector<Column> &right);

bool operator!=(const EqClasses &left, const EqClasses &right);

Matrix GetEqClassesMatrix(const Matrix &matrix, IntsMap &map);

EqClasses GetFirstEqClasses(Matrix matrix, std::vector<int> outputFunction);

EqClasses GetNewClasses(const EqClass &eqClass, int &classNumber, IntsMap &classesMap);

void FillColumn(Column &column, const Matrix &sourceTable, IntsMap &classesMap);

EqClasses GetNewEqClasses(const EqClasses &classes, const Matrix &sourceTable);

EqClasses GetMinimizedClasses(EqClasses classes, const Matrix &sourceTable);

Matrix GetMatrix(const EqClasses &classes);