#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>

#include "imgui/imgui.h"
#include "render.hpp"
#include "model.hpp"
#include "memory_table.hpp"

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
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable;
    ImVec2 avail = ImGui::GetContentRegionAvail();

    if (ImGui::BeginTable("##processTable", 6, flags, avail, 0)) //ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 15), 0.0f))
    {
        ImGui::TableSetupColumn("Offset", 0, 0.0f, MainTableOffset);
        ImGui::TableSetupColumn("Address", 0, 0.0f, MainTableAddress);
        ImGui::TableSetupColumn("Value", 0, 0.0f, MainTableValue);
        ImGui::TableSetupColumn("Hex", 0, 0.0f, MainTableValue);
        ImGui::TableSetupColumn("Integer", 0, 0.0f, MainTableValue);
        ImGui::TableSetupColumn("Floating Point", 0, 0.0f, MainTableValue);
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();

        static MemoryTable memTable;

        bool success = ReadProcessMemory(Model::hProc, (BYTE*)Model::baseAddress, memTable.byteBuffer, memTable.bufferLength, nullptr);

        if (!success)
        {
            memset(memTable.byteBuffer, 0, memTable.bufferLength);
        }

        if (memTable.dataLines->size() == 0)
        {
            memTable.constructLines();
        }

        memTable.renderLines(Model::baseAddress);

        ImGui::EndTable();
    }
}