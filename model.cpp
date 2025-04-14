#include <Windows.h>
#include <TlHelp32.h>
#include <algorithm>
#include <functional>
#include "model.hpp"
#include "process.hpp"
#include "memory.hpp"


std::vector<PROCESSENTRY32W> Model::processList;
HANDLE Model::hProc = nullptr;
uintptr_t Model::baseModuleAddress = NULL;
uintptr_t Model::baseAddress = NULL;
using namespace std::placeholders;

void Model::populateProcessList()
{
	processList.clear();
	process::getListOfAllProcesses(processList);
}

int comparePID(PROCESSENTRY32 lhs, PROCESSENTRY32 rhs, bool descending)
{
	if (descending)
	{
		return rhs.th32ProcessID > lhs.th32ProcessID;
	}
	return lhs.th32ProcessID > rhs.th32ProcessID;
}

int compareName(PROCESSENTRY32 lhs, PROCESSENTRY32 rhs, bool descending)
{
	if (descending)
	{
		return _wcsicmp(rhs.szExeFile, lhs.szExeFile) > 0;
	}
	return _wcsicmp(lhs.szExeFile, rhs.szExeFile) > 0;
}

void Model::sortProcessList(ProcessTableID tableID, bool descending)
{
	switch (tableID)
	{
	case Model::ProcessTableID_PID:
		std::sort(processList.begin(), processList.end(), std::bind(comparePID, _1, _2, descending));
		break;
	case Model::ProcessTableID_Name:
		std::sort(processList.begin(), processList.end(), std::bind(compareName, _1, _2, descending));
		break;
	default:
			break;
	}
}

void Model::openActiveProcess(PROCESSENTRY32& process)
{
	if (hProc != nullptr)
	{
		CloseHandle(hProc);
	}
	baseModuleAddress = memory::getModuleAddress(process.th32ProcessID, process.szExeFile, nullptr);
	hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, process.th32ProcessID);
}
