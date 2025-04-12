
#include <Windows.h>
#include <TlHelp32.h>
#include "process.hpp"
#include <vector>

namespace process {
	// Get ProcessId by name
	DWORD getProccessId(const wchar_t* processName)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 pe;

			pe.dwSize = sizeof(pe);

			if (Process32First(hSnap, &pe))
			{
				do
				{
					if (!_wcsicmp(pe.szExeFile, processName))
					{
						CloseHandle(hSnap);
						return pe.th32ProcessID;
					}
				} while (Process32Next(hSnap, &pe));
			}
		}
		CloseHandle(hSnap);
		return 0;
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


	void getListOfAllProcesses(std::vector<PROCESSENTRY32>& list)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 pe;

			pe.dwSize = sizeof(pe);

			if (Process32First(hSnap, &pe))
			{
				do
				{
					list.push_back(pe);
				} while (Process32Next(hSnap, &pe));
			}
		}
		CloseHandle(hSnap);
	}

	BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam)
	{
		std::vector<HWND>& list = *reinterpret_cast<std::vector<HWND>*>(lparam);
		int length = GetWindowTextLength(hWnd);
		if (length > 0 && IsWindowVisible(hWnd))
		{
			list.push_back(hWnd);
		}

		return TRUE;
	}

	void getListOfAllWindows(std::vector<HWND>& list)
	{
		EnumWindows(enumWindowCallback, reinterpret_cast<LPARAM>(&list));
	}
}
