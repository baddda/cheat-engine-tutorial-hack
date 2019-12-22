#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "Util.h"
#include "ProcessService.h"

int main()
{
	ProcessService* processService = ProcessService::getInstance();
	processService->attach();
	processService->solveStep2();

	getchar();
	return 0;
}
