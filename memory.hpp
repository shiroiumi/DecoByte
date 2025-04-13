#include <Windows.h>
#include <vector>


namespace memory
{
	uintptr_t getModuleAddress(DWORD processId, const wchar_t* moduleName, DWORD* moduleSize);
	uintptr_t findDMAAddr(HANDLE hProcess, uintptr_t baseAddr, std::vector<unsigned int> offsets);
}