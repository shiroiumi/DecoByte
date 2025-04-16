#include <format>
#include "memory_table.hpp"
#include "imgui/imgui.h"

void DataLine::renderLine(uintptr_t baseAddress, uint64_t byteValue)
{
    if (dataType == DATATYPE_HEX)
    {
        std::string hexText = std::format("{:X}", byteValue);
        std::string integerText = std::format("{:d}", byteValue);
        double doubleValue = std::bit_cast<double>(byteValue);
        std::string floatText = std::format("{:f}", doubleValue);
        if (doubleValue > 1e10 || doubleValue < -1e10)
        {
            floatText = std::format("{:.4e}", doubleValue);
        }


        char addressFmt[8] = "%0";
        strcat_s(addressFmt, ADDRESS_FMT);
        strcat_s(addressFmt, "llx");
        ImGui::PushID(offset);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%04X", offset);
        ImGui::TableNextColumn();
        ImGui::Text(addressFmt, baseAddress + offset);
        ImGui::TableNextColumn();
        ImGui::Text("???");
        ImGui::TableNextColumn();
        ImGui::Text(hexText.c_str());
        ImGui::TableNextColumn();
        ImGui::Text(integerText.c_str());
        ImGui::TableNextColumn();
        ImGui::Text(floatText.c_str());
        ImGui::PopID();
    }

}

MemoryTable::MemoryTable()
{
	dataLines = new std::vector<DataLine>();
	byteBuffer = new unsigned char[bufferLength];
}

MemoryTable::MemoryTable(char* buffer, size_t size)
{
	byteBuffer = new unsigned char[size];
    memcpy(byteBuffer, buffer, size);
	bufferLength = size;

    constructLines();
};

MemoryTable::~MemoryTable()
{
	delete dataLines;
	delete byteBuffer;
}

void MemoryTable::renderLines(uintptr_t baseAddress)
{
    for (unsigned int i = 0; i < dataLines->size(); ++i)
    {
        uint64_t byteValue = 0;
        for (size_t j = 0; j < dataLines->at(i).byteLength; ++j)
        {
            unsigned char byte = byteBuffer[dataLines->at(i).offset + j];
            byteValue |= static_cast<uint64_t>(byte) << j * 8ULL;
        }
        dataLines->at(i).renderLine(baseAddress, byteValue);
    }
}

void MemoryTable::constructLines()
{
    dataLines->clear();
    unsigned int leftOver = bufferLength % ADDRESS_LENGTH;
    size_t dataLineSize = (bufferLength / ADDRESS_LENGTH);
    dataLines = new std::vector<DataLine>(dataLineSize);

    for (size_t i = 0; i < dataLines->size(); ++i)
    {
        dataLines->at(i).offset = i * ADDRESS_LENGTH;
    }
    if (leftOver)
    {
        constructLeftOverLine(dataLines->size()*ADDRESS_LENGTH);
    }
}

void MemoryTable::constructLeftOverLine(unsigned int offset)
{
    unsigned int numOfleftOverBytes = bufferLength - offset;
    if (numOfleftOverBytes <= 0)
    {
        return;
    }

    if (numOfleftOverBytes / 8 > 0)
    {
        dataLines->push_back(DataLine(offset, DATATYPE_HEX, 8));
        constructLeftOverLine(offset + 8);
    }
    else if (numOfleftOverBytes / 4 > 0)
    {
        dataLines->push_back(DataLine(offset, DATATYPE_HEX, 4));
        constructLeftOverLine(offset + 4);
    }
    else if (numOfleftOverBytes / 2 > 0)
    {
        dataLines->push_back(DataLine(offset, DATATYPE_HEX, 2));
        constructLeftOverLine(offset + 2);
    }
    else if (numOfleftOverBytes)
    {
        dataLines->push_back(DataLine(offset, DATATYPE_HEX, 1));
        constructLeftOverLine(offset + 1);
    }
}