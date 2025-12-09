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
        if (ImGui::Begin(GetTitle(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
        {
            auto oldValue = currentValue;

            if (ImGui::SliderInt("Vol:", &currentValue, 0, 100) && currentValue != oldValue)
            {
                client->SetVolume(currentValue);
            }
        }

        ImGui::End();
    }

    VolumeControl::~VolumeControl()
    {
    }

    void VolumeControl::OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data)
    {
        if (data->idleEvent == MPD_IDLE_MIXER)
        {
            currentValue = mpd_status_get_volume(data->currentStatus);
        }
    }
} // ImMPD