#pragma once

#include "GLFW/glfw3.h"

#define DEFAULT_VIEWPORT_WIDTH 1000
#define DEFAULT_VIEWPORT_HEIGHT 1000

namespace render {
	
	// State
	struct State {
		bool ShowAttachToProcessWindow = false;
	};

	// Initialize
	GLFWwindow* initializeGLFW();
	bool initializeImgui(GLFWwindow* window);

	// Main draw function
	void draw(GLFWwindow* window);

	// Components
	void ShowMainWindow();
	void ShowMainMenuBar(State* state);
	void ShowAttachToProcessWindow(bool* pOpen, State* state);
	void ShowAttachToProcessTable(State* state);
	void ShowMainMenuTable();
}
