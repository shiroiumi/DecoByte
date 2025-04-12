
#include <iostream>
#include "imgui/imgui.h"
#include "render.hpp"
#include "model.hpp"

void render::ShowMainMenuBar(render::State* state)
{

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Attach to Process", NULL, false))
			{
				Model::populateProcessList();
				state->ShowAttachToProcessWindow = true;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
		return;
	}
}