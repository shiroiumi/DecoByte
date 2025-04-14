
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

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
	char cTitle[2048];
	size_t size;

	for (auto& hWnd : windowList)
	{
		int length = GetWindowTextLength(hWnd);
		if (length < 1024)
		{
			GetWindowTextW(hWnd, title, 1024);
			wcstombs_s(&size, cTitle, 2048, title, 2048);
			std::cout << cTitle << std::endl;
		}
	}

	for (auto& process : processList)
	{
		wcstombs_s(&size, cTitle, 2048, process.szExeFile, 2048);
		std::cout << process.th32ProcessID << ":" << cTitle << std::endl;
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