
#include "imgui/imgui.h"
#include "render.hpp"


void render::ShowMainWindow()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("DecoByte", NULL, 0))
	{
		ImGui::End();
		return;
	}

	ImGui::End();
}