
#include "imgui/imgui.h"
#include "GLFW/glfw3.h"
#include "render.hpp"
#include "model.hpp"

void render::ShowMainWindow()
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_MenuBar;

	static render::State state;

	if (state.ShowAttachToProcessWindow)
	{
		render::ShowAttachToProcessWindow(&state.ShowAttachToProcessWindow, &state);
	}

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("DecoByte", NULL, windowFlags))
	{
		ImGui::End();
		return;
	}

	render::ShowMainMenuBar(&state);
	if (Model::hProc != nullptr)
	{
		render::ShowMainMenuTable();
	}

	ImGui::End();
}