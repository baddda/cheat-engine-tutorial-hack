#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "Util.h"

class ProcessService
{
private:
	static ProcessService* instance;

	DWORD procId = 0;
	uintptr_t moduleBase = 0;
	HANDLE hProcess = 0;

	ProcessService() {};
	DWORD getProcId(const std::wstring& processName);
	uintptr_t findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName);
public:
	static ProcessService* getInstance();
	void attach();
	void solveStep2();
};
