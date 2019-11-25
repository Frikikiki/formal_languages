#include "pch.h"
#include "minCommon.h"



Column::Column(int state, std::vector<int> classesNumbers = {})
{
	this->state = state;
	this->classesNumbers = classesNumbers;
}


EqClass::EqClass(int classNumber, const std::vector<Column> &columns, const std::vector<int> &eqReason)
{
	this->classNumber = classNumber;
	this->columns = columns;
	this->eqReason = eqReason;
}


bool operator!=(const std::vector<Column> &left, const std::vector<Column> &right)
{
	if (left.size() != right.size())
	{
		return true;
	}
	for (int i = 0; i < left.size(); i++)
	{
		if (left[i].state != right[i].state ||
			left[i].classesNumbers != right[i].classesNumbers)
		{
			return true;
		}
	}
	return false;
}


bool operator!=(const EqClasses &left, const EqClasses &right)
{
	if (left.size() != right.size())
	{
		return true;
	}
	for (int i = 0; i < left.size(); i++)
	{
		if (left[i].classNumber != right[i].classNumber ||
			left[i].columns != right[i].columns)
		{
			return true;
		}
	}
	return false;
}


Matrix GetEqClassesMatrix(const Matrix &matrix, IntsMap &map)
{
	int a = matrix.size(), b = matrix[0].size();
	Matrix result(a, std::vector<int>(b));
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			IntsMap::iterator it = map.find(matrix[i][j]);
			result[i][j] = it->second;
		}
	}
	return result;
}


EqClasses GetFirstEqClasses(Matrix matrix, std::vector<int> outputFunction)
{
	IntsMap columnAndClass;
	std::map<int, std::vector<int>> classAndColumns;
	for (int i = 0; i < outputFunction.size(); i++)
	{
		columnAndClass.insert({ i, outputFunction[i] });
		std::map<int, std::vector<int>>::iterator it = classAndColumns.find(outputFunction[i]);
		if (it == classAndColumns.end())
		{
			classAndColumns.insert({ outputFunction[i], {i} });
		}
		else
		{
			it->second.push_back(i);
		}
	}
	Matrix eqClassesMatrix = GetEqClassesMatrix(matrix, columnAndClass);
	Matrix transposedEqClassesMatrix = GetTransposedMatrix(eqClassesMatrix);
	EqClasses result;
	for (std::pair<int, std::vector<int>> k : classAndColumns)
	{
		EqClass eqClass(k.first, {}, {});
		for (int i : k.second)
		{
			eqClass.columns.emplace_back(i, transposedEqClassesMatrix[i]);
		}
		result.push_back(eqClass);
	}
	return result;
}


EqClasses GetNewClasses(const EqClass &eqClass, int &classNumber, IntsMap &classesMap)
{
	EqClasses result;
	for (const Column &column : eqClass.columns)
	{
		bool isColumnInSomeClass = false;
		for (const EqClass &resClass : result)
		{
			if (column.classesNumbers == resClass.eqReason)
			{
				resClass.columns.emplace_back(column.state);
				classesMap.insert({ column.state, resClass.classNumber });
				isColumnInSomeClass = true;
				break;
			}
		}
		if (!isColumnInSomeClass)
		{
			result.emplace_back(classNumber, std::vector<Column>(1, Column(column.state)), column.classesNumbers);
			classesMap.insert({ column.state, classNumber });
			classNumber++;
		}
	}
	return result;
}


void FillColumn(Column &column, const Matrix &sourceTable, IntsMap &classesMap)
{
	for (int i : sourceTable[column.state])
	{
		IntsMap::iterator it = classesMap.find(i);
		column.classesNumbers.push_back(it->second);
	}
}


EqClasses GetNewEqClasses(const EqClasses &classes, const Matrix &sourceTable)
{
	EqClasses result;
	int newClassNumber = 1;
	IntsMap classesMap;
	for (const EqClass &eqClass : classes)
	{
		EqClasses newClasses = GetNewClasses(eqClass, newClassNumber, classesMap);
		result.insert(result.end(), newClasses.begin(), newClasses.end());
	}
	for (EqClass &eqClass : result)
	{
		for (Column &column : eqClass.columns)
		{
			FillColumn(column, GetTransposedMatrix(sourceTable), classesMap);
		}
	}
	return result;
}


EqClasses GetMinimizedClasses(EqClasses classes, const Matrix &sourceTable)
{
	EqClasses newClasses = GetNewEqClasses(classes, sourceTable);
	while (newClasses != classes)
	{
		classes = newClasses;
		newClasses = GetNewEqClasses(classes, sourceTable);
	}
	return newClasses;
}


Matrix GetMatrix(const EqClasses &classes)
{
	Matrix matrix;
	for (const EqClass &eqClass : classes)
	{
		matrix.push_back(eqClass.columns[0].classesNumbers);
	}
	return GetTransposedMatrix(matrix);
}