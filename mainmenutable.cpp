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
        ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 0.0f, MainTableAddress);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 0.0f, MainTableValue);
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();



        BYTE byteArray[1024];

        ReadProcessMemory(Model::hProc, (BYTE*)Model::baseAddress, &byteArray, sizeof(byteArray), nullptr);

        int selected = -1;
        for (int row = 0; row < 1024; row+=8)
        {
            // Display a data item

            ImGui::PushID(Model::baseAddress + row);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%04X", row);
            ImGui::TableNextColumn();
            ImGui::Text("%016llX", Model::baseAddress + row);
            ImGui::TableNextColumn();
            ImGui::Text("%llX", (unsigned long long)byteArray[row] |
                ((unsigned long long)byteArray[row + 1]) << 8 |
                (unsigned long long)byteArray[row + 2] << 16 |
                (unsigned long long)byteArray[row + 3] << 24 |
                (unsigned long long)byteArray[row + 4] << 32 |
                (unsigned long long)byteArray[row + 5] << 40 |
                (unsigned long long)byteArray[row + 6] << 48 |
                (unsigned long long)byteArray[row + 7] << 56 );
            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}