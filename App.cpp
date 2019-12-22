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

	getchar();
	return 0;
}
