#include "MachineRunner.h"

MachineRunner::MachineRunner(std::string fileName, Machine& machine)
{
	m_machine = machine.GetMachine();
	m_separators = machine.GetSeparators();
	m_inputFile.open(fileName);
	if (!m_inputFile.is_open())
	{
		throw std::invalid_argument("The file could not be opened\n");
	}
}


bool MachineRunner::DoesContainSep(std::string token)
{
	for (auto ch : token)
	{
		if (m_separators.count(std::string(1, ch)) == 0)
		{
			return false;
		}
	}
	return true;
}


void MachineRunner::Run()
{
	if (m_inputFile.eof())
		return;
	
	int row = 1;
	int column = 1;
	
	int rowNumber = 1;
	int nextState = 1;
	std::string currentToken;
	std::ofstream outpuFile("result.txt");
	char ch;

	while (m_inputFile.get(ch))
	{		
		std::string currentChar(1, ch);
		std::optional<std::string> tokenAnalysisResult;
		if (currentChar == "\n")
		{
			tokenAnalysisResult = GetTokenType(nextState, "eol", currentToken);
		}
		else if (currentChar == "\t")
		{
			tokenAnalysisResult = GetTokenType(nextState, "tab", currentToken);
		}
		else if (currentChar == " ")
		{
			tokenAnalysisResult = GetTokenType(nextState, "space", currentToken);
		}
		else 
		{
			tokenAnalysisResult = GetTokenType(nextState, currentChar, currentToken);
		}

		if (m_runningState == RunningState::ERROR && tokenAnalysisResult.has_value())
		{
			outpuFile << rowNumber << ". " << currentToken  << " " << tokenAnalysisResult.value() << "  -  " << row << ", " << column << std::endl;
			rowNumber++;
			currentToken = "";
			m_runningState = RunningState::UNDEFINED;
			if (ch != '\n')
			{
				m_inputFile.seekg(-1, m_inputFile.cur);
			}
		}
		else if (m_runningState == RunningState::ESCAPE || (!tokenAnalysisResult.has_value() && 
			m_runningState != RunningState::COMMENT && m_runningState != RunningState::LINE_COMMENT) || 
			m_runningState == RunningState::ERROR || (m_runningState == RunningState::STRING && !tokenAnalysisResult.has_value()))
		{
			currentToken += currentChar;
			if (m_runningState == RunningState::ESCAPE && tokenAnalysisResult.has_value())
			{
				m_runningState = RunningState::STRING;
			}
		}
		else if (tokenAnalysisResult.has_value())
		{	
			std::string value = tokenAnalysisResult.value();
			if (m_runningState == RunningState::MISS)
			{
				if (currentToken != "")
				{
					outpuFile << rowNumber << ". " << currentToken << " " << value << "  -  " << row << ", " << column << std::endl;
					rowNumber++;
					currentToken = "";
				}
			}
			else if (m_runningState == RunningState::COMMENT || m_runningState == RunningState::LINE_COMMENT)
			{
				currentToken = "";
			}
			else if (m_runningState == RunningState::TOKEN)
			{
				if (!DoesContainSep(currentToken))
				{
					m_inputFile.seekg(-1, m_inputFile.cur);
					m_runningState = RunningState::SEPARATOR;
				}
				else if (m_separators.count(currentChar) != 0)
				{
					currentToken += currentChar;
				}
				else
				{
					m_inputFile.seekg(-1, m_inputFile.cur);
				}
				if (value == "decimal number")
				{
					try
					{
						std::stoi(currentToken);
						std::stod(currentToken);
					}
					catch(std::out_of_range e)
					{
						value = "ERROR";
					}
				}
				outpuFile << rowNumber << ". " << currentToken << " " << value << "  -  " << row << ", " << column << std::endl;
				rowNumber++;
				currentToken = "";
			}
			else if (m_runningState == RunningState::SEPARATOR || m_runningState == RunningState::STRING)
			{	
				outpuFile << rowNumber << ". " << currentToken + currentChar << " " << value << "  -  " << row << ", " << column << std::endl;
				currentToken = "";
				rowNumber++;
				m_runningState = RunningState::UNDEFINED;
			}
		}
		column++;
		if (ch == '\n')
		{
			row++;
			column = 1;
		}
	}
	if (m_inputFile.eof() && m_runningState == RunningState::COMMENT)
	{
		outpuFile << rowNumber << ". " << "ERROR. Unclosed comment.";
	}
	else if (m_inputFile.eof() && currentToken != "")
	{
		std::optional<std::string> tokenAnalysisResult = GetTokenType(nextState, "eof", currentToken);
		if (tokenAnalysisResult.has_value())
			outpuFile << rowNumber << ". " << currentToken << " " << tokenAnalysisResult.value() << "  -  " << row << ", " << column << std::endl;
	}
}

std::optional<std::string> MachineRunner::GetTokenType(int &state, const std::string &input, std::string &currentToken)
{
	try
	{
		if (m_runningState == RunningState::ERROR)
		{
			if (m_separators.count(input) != 0 || input == " " || input == "\n" || input == "\t")
			{
				return "ERROR";
			}
			else
			{
				return {};
			}
		}
		int nextState = std::stoi(m_machine[state][input]);
		if(m_runningState != RunningState::STRING)
			state = nextState;
		return {};
	}
	catch (std::invalid_argument exception)
	{
		std::string result = m_machine[state][input];
		if (m_runningState == RunningState::COMMENT)
		{
			if (result == "comment")
			{
				m_runningState = RunningState::UNDEFINED;
			}
		}
		else if (result == "comment")
		{
			m_runningState = RunningState::COMMENT;
		}
		else if (m_runningState == RunningState::LINE_COMMENT)
		{
			if (input == "eol")
			{
				m_runningState = RunningState::UNDEFINED;
			}
		}
		else if (result == "line comment")
		{
			m_runningState = RunningState::LINE_COMMENT;
		}
		else if (m_runningState == RunningState::STRING)
		{
			if (input == "eol")
			{
				m_runningState = RunningState::ERROR;
				state = 1;
				return "ERROR";
			}
			else if (result == "escape")
			{
				m_runningState = RunningState::ESCAPE;
				return {};
			}
			else if (result != "string")
				return {};
		}
		else if (result == "string")
		{
			m_runningState = RunningState::STRING;
			return {};
		}
		else if (m_runningState == RunningState::ESCAPE)
		{
			if (input == "eol")
			{
				m_runningState = RunningState::ERROR;
				state = 1;
				return "ERROR";
			}
		}
		else if (result == "")
		{
			m_runningState = RunningState::ERROR;
			state = 1;
			return {};
		}
		else if (m_separators.count(input) != 0)
		{
			if (currentToken == "")
			{
				m_runningState = RunningState::SEPARATOR;
			}
			if(m_runningState != RunningState::SEPARATOR)
				m_runningState = RunningState::TOKEN;
		}
		else if (result == "miss")
		{
			m_runningState = RunningState::MISS;
		}
		else
		{
			m_runningState = RunningState::TOKEN;
		}
		state = 1;
		return result;
	}
}
