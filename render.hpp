#pragma once

#include "GLFW/glfw3.h"

#define DEFAULT_VIEWPORT_WIDTH 400
#define DEFAULT_VIEWPORT_HEIGHT 400

namespace render {

	// Initialize
	GLFWwindow* initializeGLFW();
	bool initializeImgui(GLFWwindow* window);

	// Main draw function
	void draw(GLFWwindow* window);

	// Components
	void ShowMainWindow();
}
