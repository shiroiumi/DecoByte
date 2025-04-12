#include <Windows.h>
#include <TlHelp32.h>
#include <algorithm>
#include <functional>
#include "model.hpp"
#include "process.hpp"


std::vector<PROCESSENTRY32W> Model::processList;
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
		return wcscmp(rhs.szExeFile, lhs.szExeFile) > 0;
	}
	return wcscmp(lhs.szExeFile, rhs.szExeFile) > 0;
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