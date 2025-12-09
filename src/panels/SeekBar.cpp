#include "SeekBar.hpp"
#include "imgui.h"
#include "GLFW/glfw3.h"


void ImMPD::SeekBar::Draw(MpdClientWrapper *client)
{
    //Set state on the first draw.
    if (!initialized)
    {
        auto song = client->GetCurrentSong();
        auto status = client->GetStatus();
        SetState(song, status);
        mpd_song_free(song);
        mpd_status_free(status);

        initialized = true;
    }

    if(ImGui::Begin(GetTitle(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
    {
        bool disabled = currentState == MPD_STATE_STOP || currentState == MPD_STATE_UNKNOWN;

        ImGui::BeginDisabled(disabled);

        bool seeking = currentSeek >= 0;

        currentSeek = seeking ? currentSeek : currentElapsedSeconds;

        if (!seeking && currentState == MPD_STATE_PLAY)
        {
            currentSeek += glfwGetTime() - elapsedSecondsSetAtTime;
        }

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::SliderFloat("##", &currentSeek, 0, currentDuration);

        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            printf("Seeking to %f\n", currentSeek);
            client->SeekToSeconds(currentSeek, false);
        }

        if (!ImGui::IsItemActive())
        {
            currentSeek = -1;
        }

        ImGui::EndDisabled();
    }

    ImGui::End();
}

const char *ImMPD::SeekBar::GetTitle()
{
    return "Seekbar";
}

void ImMPD::SeekBar::OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data)
{
    if ((data->idleEvent & MPD_IDLE_PLAYER) != 0)
    {
        SetState(data->currentSong, data->currentStatus);
    }
}

void ImMPD::SeekBar::SetState(mpd_song *song, mpd_status *status)
{
    currentState = mpd_status_get_state(status);
    if (currentState == MPD_STATE_PLAY || currentState == MPD_STATE_PAUSE)
    {
        currentElapsedSeconds = mpd_status_get_elapsed_ms(status) / 1000.0f;
        currentDuration = mpd_song_get_duration_ms(song) / 1000.0f;
        elapsedSecondsSetAtTime = glfwGetTime();
    }
    else
    {
        currentElapsedSeconds = currentDuration = 0;
        elapsedSecondsSetAtTime = 0;
    }
}

ImMPD::SeekBar::SeekBar()
{

}

ImMPD::SeekBar::~SeekBar()
= default;
