#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>

const std::string MEALY = "mealy";
const std::string MOORE = "moore";
const std::string DOT_FILE_NAME = "temp.dot";
const std::string LABEL_PART = " [label=x";
const std::string DIGRAPH_PART = "digraph G{";
const std::string SEMICOLON = ";";
const std::string CLOSING_BRACE = "}";
const std::string CLOSING_BRACKET = "]";
const std::string ARROW = "->";
const std::string SPACE = " ";

using Matrix = std::vector<std::vector<int>>;
using StringMatrix = std::vector<std::vector<std::string>>;


void GetParams(int &vertexCount, int &inSymbolsCount,
	int &outSymbolsCount, std::string &machineType);

int GetIndex(std::string str);