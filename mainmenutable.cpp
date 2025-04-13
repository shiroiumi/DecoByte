#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>

#include "imgui/imgui.h"
#include "render.hpp"
#include "model.hpp"

enum MainTable
{
    MainTableOffset,
    MainTableAddress,
    MainTableValue
};

void render::ShowMainMenuTable()
{
    static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollX
        | ImGuiTableFlags_RowBg;

    if (ImGui::BeginTable("##processTable", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 15), 0.0f))
    {
        ImGui::TableSetupColumn("Offset", ImGuiTableColumnFlags_WidthFixed, 0.0f, MainTableOffset);
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 0.0f, MainTableAddress);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 0.0f, MainTableValue);
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();



        BYTE byteArray[1024];

        ReadProcessMemory(Model::hProc, (BYTE*)Model::baseModuleAddress, &byteArray, sizeof(byteArray), nullptr);

        int selected = -1;
        for (int row = 0; row < 1024; row+=8)
        {
            // Display a data item

            ImGui::PushID(Model::baseModuleAddress + row);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%04x", row);
            ImGui::TableNextColumn();
            ImGui::Text("%016x", Model::baseModuleAddress + row);
            ImGui::TableNextColumn();
            ImGui::Text("%x", (unsigned long long)byteArray[row]);
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}