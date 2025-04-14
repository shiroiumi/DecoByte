#include <string>
#include "imgui/imgui.h"
#include "render.hpp"

static int StringInputTextCallback(ImGuiInputTextCallbackData* data)
{
    std::string* str = (std::string*)data->UserData;
    IM_ASSERT(data->Buf == str->c_str());
    str->resize(data->BufTextLen);
    data->Buf = (char*)str->c_str();
    return 0;
}

bool render::StringTextInput(const char* label, std::string* str, ImGuiInputTextFlags flags)
{
    ImGuiInputTextFlags test = flags & ImGuiInputTextFlags_CallbackResize;
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    return ImGui::InputText(label, (char*)str->c_str(), (size_t)str->capacity() + 1,
        flags | ImGuiInputTextFlags_CallbackResize, StringInputTextCallback, (void*)str);
    return false;
}