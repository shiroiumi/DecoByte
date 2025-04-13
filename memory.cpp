#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

namespace memory {
	uintptr_t findDMAAddr(HANDLE hProcess, uintptr_t baseAddr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = baseAddr;

		for (int i = 0; i < offsets.size(); ++i)
		{
			ReadProcessMemory(hProcess, (BYTE*)addr, &addr, sizeof(addr), 0);
			addr += offsets[i];
		}

		return addr;
	}

	// Get the module address
	uintptr_t getModuleAddress(DWORD processId, const wchar_t* moduleName, DWORD* moduleSize)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

		if (hSnap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 me;

			me.dwSize = sizeof(me);

			if (Module32First(hSnap, &me))
			{
				do
				{
					if (!_wcsicmp(me.szModule, moduleName))
					{
						CloseHandle(hSnap);
						if (moduleSize != nullptr)
						{
							*moduleSize = me.modBaseSize;
						}
						return (uintptr_t)me.modBaseAddr;
					}
				} while (Module32Next(hSnap, &me));
			}
			CloseHandle(hSnap);
			return 0;
		}
		return 0;
	}
}