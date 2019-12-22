#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "Util.h"

class ProcessService
{
private:
	static ProcessService* instance;

	ProcessService() {};
	DWORD GetProcId(const std::wstring& processName);
	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
public:
	static ProcessService* getInstance();
	void attach();
};
