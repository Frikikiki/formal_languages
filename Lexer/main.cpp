#include "MachineRunner.h"

int main()
{
	try
	{
		Machine machine("machine.txt");
		MachineRunner runner("code.txt", machine);
		runner.Run();
	}
	catch (std::invalid_argument ex)
	{
		std::cout << ex.what();
	}
}