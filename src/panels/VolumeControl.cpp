//
// Created by aiden on 2025-12-09.
//

#include "VolumeControl.hpp"

#include "imgui.h"

namespace ImMPD {
    const char * VolumeControl::GetTitle()
    {
        return "Volume Control";
    }

    void VolumeControl::Draw(MpdClientWrapper *client)
    {
        if (ImGui::Begin(GetTitle()))
        {

        }

        ImGui::End();
    }

    VolumeControl::~VolumeControl()
    {
    }
} // ImMPD