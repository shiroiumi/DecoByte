#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>

#include "imgui/imgui.h"
#include "render.hpp"
#include "model.hpp"


void render::ShowAttachToProcessTable(State* state)
{
	static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollY
		| ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollX
        | ImGuiTableFlags_RowBg;

	if (ImGui::BeginTable("##processTable", 2, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 15), 0.0f))
	{
		ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, Model::ProcessTableID_PID);
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 0.0f, Model::ProcessTableID_Name);
		ImGui::TableSetupScrollFreeze(0, 1);
		ImGui::TableHeadersRow();

        if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs())
        {
            if (sort_specs->SpecsDirty)
            {
                for (int i = 0; i < sort_specs->SpecsCount; i++)
                {
                    Model::sortProcessList((Model::ProcessTableID)sort_specs[i].Specs->ColumnUserID, sort_specs[i].Specs->SortDirection != ImGuiSortDirection_Descending);
                }
                sort_specs->SpecsDirty = false;
            }
        }

        ImGuiListClipper clipper;
        clipper.ItemsCount = 40;
        clipper.Begin(Model::processList.size());
        int selected = -1;
        while (clipper.Step())
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            {
                // Display a data item
                PROCESSENTRY32 process = Model::processList[row];
 
                char processName[2048];
                size_t size;
                wcstombs_s(&size, processName, 2048, process.szExeFile, 2048);
                char label[64];
                sprintf_s(label, "%05d", process.th32ProcessID);

                ImGui::PushID(process.th32ProcessID);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Selectable(label,
                    process.th32ProcessID == selected,
                    ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap))
                {
                    selected = process.th32ProcessID;
                    Model::openActiveProcess(process);
                    state->ShowAttachToProcessWindow = false;
                }
                ImGui::TableNextColumn();
                ImGui::TextUnformatted(processName);
                ImGui::PopID();
            }

		ImGui::EndTable();
	}
}