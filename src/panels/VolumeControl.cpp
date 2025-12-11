//
// Created by aiden on 2025-12-09.
//

#include "VolumeControl.hpp"

#include "imgui.h"

namespace ImMPD {
    void VolumeControl::SetState(mpd_status *status)
    {
        if (status == nullptr)
        {
            return;
        }

        currentValue = mpd_status_get_volume(status);
    }

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
                client->BeginNoIdle();
                client->SetVolume(currentValue);
                client->EndNoIdle();
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
            SetState(data->currentStatus);
        }
    }

    void VolumeControl::InitState(MpdClientWrapper *client)
    {
        client->BeginNoIdle();
        auto status = client->GetStatus();
        SetState(status);
        if (status != nullptr)
        {
            mpd_status_free(status);
        }
        client->EndNoIdle();
    }
} // ImMPD