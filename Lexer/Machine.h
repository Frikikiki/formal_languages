#pragma once
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iostream>

using MachineHandler = std::map<int, std::map<std::string, std::string>>;
enum class MachineElement {CURRENT_STATE, NEXT_STATE, INPUT, OUTPUT, UNDEFINED};


class Machine
{
public:
    Machine(std::string fileName);
    MachineHandler GetMachine();
    std::set<std::string> GetSeparators();

private:
    std::ifstream m_inputFile;
    MachineHandler m_handler;
    std::set<std::string> m_codeSeparators;
 
    void FillMachine();
    void AnalyzeLine(std::string fileString, int& currentState, std::string& machineInput, std::string& nextState);

    std::string m_machineSeparator = " - ";
    void ReadSeparators();
    bool IsSeparatorNext(std::string str, int index);
};