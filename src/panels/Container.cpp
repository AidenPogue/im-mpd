//
// Created by aiden on 2025-12-11.
//

#include "Container.hpp"

#include "imgui.h"

const char *ImMPD::Container::GetTitle()
{
    return "Container";
}

void ImMPD::Container::Draw(MpdClientWrapper *client)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Container");
    ImGui::DockSpace(10);
    ImGui::End();
    ImGui::PopStyleVar();
}
