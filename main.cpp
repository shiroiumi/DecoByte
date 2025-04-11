
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "render.hpp"


int main()
{
	GLFWwindow* window = render::initializeGLFW();
	render::initializeImgui(window);

	while (!glfwWindowShouldClose(window))
	{
		render::draw(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}