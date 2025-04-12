
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include <codecvt>
#include <locale>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "render.hpp"
#include "process.hpp"


int main()
{
	GLFWwindow* window = render::initializeGLFW();
	render::initializeImgui(window);

	std::vector<PROCESSENTRY32> processList;
	std::vector<HWND> windowList;

	process::getListOfAllProcesses(processList);
	process::getListOfAllWindows(windowList);

	SetConsoleOutputCP(CP_UTF8);

	wchar_t title[1024];

	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;

	for (auto& hWnd : windowList)
	{
		int length = GetWindowTextLength(hWnd);
		if (length < 1024)
		{
			GetWindowTextW(hWnd, title, 1024);
			std::cout << utf8_conv.to_bytes(title) << std::endl;
		}
	}

	for (auto& process : processList)
	{
		std::cout << process.th32ProcessID << ":" << utf8_conv.to_bytes(process.szExeFile) << std::endl;
	}

	while (!glfwWindowShouldClose(window))
	{
		render::draw(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}