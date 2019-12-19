#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

DWORD GetProcId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	if (Process32First(processesSnapshot, &processInfo)) {
		do
		{
			std::wcout << "Found process: " << processInfo.szExeFile << std::endl;
			if (!processName.compare(processInfo.szExeFile))
			{
				CloseHandle(processesSnapshot);
				return processInfo.th32ProcessID;
			}
		} while (Process32Next(processesSnapshot, &processInfo));
	}

	CloseHandle(processesSnapshot);
	return 0;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				std::wcout << "Found module: " << modEntry.szModule << std::endl;
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					std::cout << "Found base address: " << "0x" << std::hex << modBaseAddr << std::endl;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProc, (BYTE*)(addr), &addr, sizeof(addr), 0);
		addr = addr + offsets[i];
	}
	return addr;
}

int main()
{
	DWORD procId = GetProcId(L"Cheat Engine Tutorial Hack.exe");
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Cheat Engine Tutorial Hack.exe");
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	if (hProcess && moduleBase && procId) {
		uintptr_t dynamicPtrBaseAddr = moduleBase + 0x2015D0; // Why is the moduleBase always different?
		std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

		//uintptr_t test = 0;
		//ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &test, sizeof(test), nullptr);
		//std::cout << "test = " << "0x" << std::hex << test << std::endl;

		std::vector<unsigned int> ammoOffsets = { 0x480, 0x0 };
		uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
		std::cout << "ammoAddr = " << "0x" << std::hex << ammoAddr << std::endl;

		int ammoValue = 0;
		ReadProcessMemory(hProcess, (LPVOID)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
		std::cout << "Curent ammo = " << std::dec << ammoValue << std::endl;

		int newAmmo = 1337;
		WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
		std::cout << "New ammo = " << std::dec << ammoValue << std::endl;

	}
	getchar();
	return 0;
}
