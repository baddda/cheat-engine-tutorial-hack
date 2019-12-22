#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "Util.h"
#include "ProcessService.h"

int main()
{
	DWORD procId = GetProcId(L"Tutorial-i386.exe");
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Tutorial-i386.exe");
	HANDLE hProcess = 0;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	if (!hProcess)
	{
		PrintLastErrorMessage();
	}

	if (hProcess && /*moduleBase &&*/ procId) {
		uintptr_t dynamicPtrBaseAddr = moduleBase + 0x2015D0;
		std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

		std::vector<unsigned int> ammoOffsets = { 0x480 };
		uintptr_t healthAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
		std::cout << "healthAddr = " << "0x" << std::hex << healthAddr << std::endl;

		int healtValue = 0;
		ReadProcessMemory(hProcess, (LPVOID)healthAddr, &healtValue, sizeof(healtValue), nullptr);
		std::cout << "healtValue = " << std::dec << healtValue << std::endl;

		int newHealth = 1000;
		WriteProcessMemory(hProcess, (LPVOID*)healthAddr, &newHealth, sizeof(newHealth), nullptr);
		ReadProcessMemory(hProcess, (LPVOID*)healthAddr, &healtValue, sizeof(healtValue), nullptr);
		std::cout << "newHealth = " << std::dec << healtValue << std::endl;

	}
	getchar();
	return 0;
}
