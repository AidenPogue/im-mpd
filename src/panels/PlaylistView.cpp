//
// Created by aiden on 2025-12-10.
//

#include "PlaylistView.hpp"

#include "imgui.h"

namespace ImMPD
{
    void PlaylistView::GetPlaylist(MpdClientWrapper *client)
    {
        client->BeginNoIdle();
        client->GetCurrentQueue(currentPlaylist);
        client->EndNoIdle();
    }

    const char * PlaylistView::GetTitle()
    {
        return "Playlist View";
    }

    void PlaylistView::Draw(MpdClientWrapper *client)
    {
        if (ImGui::Begin(GetTitle()))
        {
            ImGui::BeginTable("plTable", 4);
            for (mpd_song *song : currentPlaylist)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text(mpd_song_get_tag(song, MPD_TAG_TITLE, 0));
                ImGui::TableNextColumn();
                ImGui::Text(mpd_song_get_tag(song, MPD_TAG_ARTIST, 0));
                ImGui::TableNextColumn();
                ImGui::Text(mpd_song_get_tag(song, MPD_TAG_ALBUM, 0));
                ImGui::TableNextColumn();
                ImGui::Text("%d", mpd_song_get_duration_ms(song));
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }

    void PlaylistView::OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data)
    {
    }

    void PlaylistView::InitState(MpdClientWrapper *client)
    {
        GetPlaylist(client);
    }

    PlaylistView::PlaylistView()
    {
        currentPlaylist = std::vector<mpd_song *>();
    }
} // ImMPD