#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "render.hpp"

void window_refresh_callback(GLFWwindow* window)
{
	render::draw(window);
	glFinish(); // important, this waits until rendering result is actually visible, thus making resizing less ugly
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* render::initializeGLFW()
{
	// Initialize GLFW
	glfwInit();

	// Let GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a new window
	GLFWwindow* window = glfwCreateWindow(DEFAULT_VIEWPORT_WIDTH, DEFAULT_VIEWPORT_HEIGHT, "DecoByte", NULL, NULL);

	// Error check
	if (window == NULL)
	{
		std::cout << "Window failed to create" << std::endl;
		glfwTerminate();
		return NULL;
	}

	// The selected window to do work
	glfwMakeContextCurrent(window);

	// Reduce tearing?
	glfwSwapInterval(1);

	// Use glad to load OpenGL libraries for use
	gladLoadGL();

	glfwSetWindowRefreshCallback(window, window_refresh_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, DEFAULT_VIEWPORT_WIDTH, DEFAULT_VIEWPORT_HEIGHT);

	return window;
}

bool render::initializeImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	return true;
}

void render::draw(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	render::ShowMainWindow();
	ImGui::ShowDemoWindow();
	ImGui::Render();

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}