#include "imgui/imgui.h"
#include "render.hpp"


void render::ShowAttachToProcessWindow(bool* pOpen)
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Select Process to Attach", pOpen))
	{
		ImGui::End();
		return;
	}
	render::ShowAttachToProcessTable();
	ImGui::End();
}