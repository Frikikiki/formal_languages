#pragma once
#include "Machine.h"
#include <string>
#include <optional>

enum class RunningState
{
	ERROR,
	COMMENT,
	LINE_COMMENT,
	STRING,
	ESCAPE,
	TOKEN,
	SEPARATOR,
	MISS,
	UNDEFINED
};


class MachineRunner
{
public:
	MachineRunner(std::string fileName, Machine& machine);
	void Run();

private:
	std::ifstream m_inputFile;
	MachineHandler m_machine;
	RunningState m_runningState = RunningState::UNDEFINED;
	std::set<std::string> m_separators;

	bool DoesContainSep(std::string token);
	std::optional<std::string> GetTokenType(int &state, const std::string &input, std::string &currentToken);
};
