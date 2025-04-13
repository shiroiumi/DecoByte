#include "imgui/imgui.h"
#include "render.hpp"
#include "model.hpp"

void render::ShowAttachToProcessWindow(bool* pOpen, State* state)
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Select Process to Attach", pOpen))
	{
		ImGui::End();
		return;
	}
	render::ShowAttachToProcessTable(state);

	ImGui::End();
}