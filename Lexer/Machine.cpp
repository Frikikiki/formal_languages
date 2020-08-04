#include "Machine.h"


Machine::Machine(std::string fileName)
{
    m_inputFile.open(fileName);
    if (!m_inputFile.is_open())
    {
        throw std::invalid_argument("The file could not be opened\n");
    }
    FillMachine();
}



std::set<std::string> Machine::GetSeparators()
{
    return m_codeSeparators;
}
MachineHandler Machine::GetMachine()
{
    return m_handler;
}



void Machine::ReadSeparators()
{
    std::string str;
    std::getline(m_inputFile, str);
    std::stringstream ss(str);
    while (ss >> str)
    {
        m_codeSeparators.insert(str);
    }
}


bool Machine::IsSeparatorNext(std::string str, int index)
{
    if (str.substr(index, m_machineSeparator.size()) == m_machineSeparator)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Machine::AnalyzeLine(std::string fileString, int& currentState, std::string& machineInput, std::string& nextState)
{
    MachineElement currentElement = MachineElement::CURRENT_STATE;
    std::string currentSubstring = "";

    for (unsigned int i = 0; i < fileString.size(); i++)
    {
        if (!IsSeparatorNext(fileString, i))
            currentSubstring += fileString[i];
        if (IsSeparatorNext(fileString, i) || i == fileString.size() - 1)
        {
            if (currentElement == MachineElement::CURRENT_STATE)
            {
                currentState = std::stoi(currentSubstring);
                currentElement = MachineElement::INPUT;
            }
            else if (currentElement == MachineElement::INPUT)
            {
                machineInput = currentSubstring;
                currentElement = MachineElement::NEXT_STATE;
            }
            else if (currentElement == MachineElement::NEXT_STATE)
            {
                nextState = currentSubstring;
                currentElement = MachineElement::CURRENT_STATE;
            }
            currentSubstring = "";
            i += m_machineSeparator.size() - 1;
        }
    }
}

void Machine::FillMachine()
{
    ReadSeparators();
    std::string fileString;
    while (getline(m_inputFile, fileString))
    {
        
        if (fileString.substr(0, 5) == "/////" || fileString == "")
        {
            continue;
        }

        int currentState;
        std::string machineInput;
        std::string nextState;

        AnalyzeLine(fileString, currentState, machineInput, nextState);

        m_handler[currentState][machineInput] = nextState;
    }
}