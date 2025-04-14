#include "exprtk/exprtk.hpp"
#include <Windows.h>
#include <string>
#include <regex>
#include <vector>
#include "imgui/imgui.h"
#include "render.hpp"
#include "model.hpp"
#include "memory.hpp"



bool parseAddressInput(std::string address)
{
	std::string expressionString;
	std::vector<std::string> operationList;
	std::vector<std::string> symbolList;

	std::regex operations("[+-]");
	std::regex module(R"(\s*<(.+)>\s*)");
	std::regex hex(R"(\s*(?:0x)?[0-9a-fA-F]+\s*)");
	std::sregex_token_iterator symbolIter(address.begin(), address.end(), operations, -1);
	std::sregex_token_iterator tEnd;
	std::smatch symbolMatch;
	size_t size;

	for (; symbolIter != tEnd; ++symbolIter)
	{
		std::string symbol = *symbolIter;
		if (std::regex_match(symbol, symbolMatch, module))
		{
			wchar_t moduleNameBuffer[1024];
			std::string moduleName = symbolMatch[1].str();
			const char* cString = moduleName.c_str();
			mbsrtowcs_s(&size, moduleNameBuffer, 1024, &cString, symbolMatch[0].str().size(), NULL);

			uintptr_t moduleAddress = memory::getModuleAddress(GetProcessId(Model::hProc), moduleNameBuffer, NULL);
			symbolList.push_back(std::to_string(moduleAddress));
		}
		else if (std::regex_match(symbol, symbolMatch, hex))
		{
			symbolList.push_back(std::to_string(stoul(symbolMatch[0].str(), 0, 16)));
		}
		else
		{
			return false;
		}
	}

	std::sregex_iterator operationIter(address.begin(), address.end(), operations);
	std::sregex_iterator sEnd;
	for (; operationIter != sEnd; ++operationIter)
	{
		for (int i = 0; i < operationIter->size(); ++i)
		{
			operationList.push_back((*operationIter)[i]);
		}
	}

	int i = 0;
	if (symbolList.size() > 0)
	{
		expressionString += symbolList[0];
	}
	while (i < operationList.size() && i+1 < symbolList.size())
	{
		expressionString += operationList[i];
		expressionString += symbolList[i+1];
		i++;
	}

	exprtk::expression<long double> expression;
	exprtk::parser<long double> parser;
	
	if (parser.compile(expressionString, expression))
	{
		unsigned long long result = (unsigned long long)expression.value();

		Model::baseAddress = result;
		return true;
	}
	else
	{
		return false;
	}
}

void render::ShowAddressTextInput()
{
	static std::string address;
	static bool showErrorMessage = false;

	render::StringTextInput("##addressLabel", &address, 0);
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (!parseAddressInput(address))
		{
			showErrorMessage = true;
		}
		else
		{
			showErrorMessage = false;
		}
	}
	if (showErrorMessage)
	{
		ImGui::TextColored(ImVec4(1.0, 0.0f, 0.0f, 1.0f), "Can't parse the address");
	}
}