#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>



struct Model
{
	enum ProcessTableID
	{
		ProcessTableID_PID,
		ProcessTableID_Name,
	};


	static std::vector<PROCESSENTRY32> processList;
	
	static void populateProcessList();

	static void sortProcessList(ProcessTableID tableID, bool descending);
};



