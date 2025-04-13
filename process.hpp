#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

namespace process
{
	DWORD getProccessId(const wchar_t* processName);
	void getListOfAllProcesses(std::vector<PROCESSENTRY32>& list);
	void getListOfAllWindows(std::vector<HWND>& list);
}