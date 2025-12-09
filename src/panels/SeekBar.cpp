#include "SeekBar.hpp"
#include "imgui.h"
#include "GLFW/glfw3.h"


void ImMPD::SeekBar::Draw(MpdClientWrapper *client)
{
    static bool seeking;
    static float seekedTo;
    auto info = client->GetCurrentPlayInfo();

    if(ImGui::Begin(GetTitle(), nullptr, ImGuiWindowFlags_NoScrollbar))
    {
        auto curSong = client->GetCurrentSong();
        if (curSong != nullptr)
        {
            seekedTo = seeking ? seekedTo : info.startedAtElapsedSeconds;

            if (!seeking && info.isPlaying)
            {
                seekedTo += (glfwGetTime() - info.startedAtGlfwTime);
            }

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::SliderFloat("##", &seekedTo, 0, mpd_song_get_duration_ms(curSong) / 1000.0f);
            
            seeking = ImGui::IsItemActive();

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                printf("Seeking to %f\n", seekedTo);
                client->SeekToSeconds(seekedTo, false);
            }
        }

    }

    ImGui::End();
}

const char *ImMPD::SeekBar::GetTitle()
{
    return "Seekbar";
}

ImMPD::SeekBar::~SeekBar()
= default;