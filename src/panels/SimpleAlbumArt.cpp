#include "SimpleAlbumArt.hpp"
#include "imgui.h"
#include "../Utils.hpp"


void ImMPD::SimpleAlbumArt::LoadArtTexture(MpdClientWrapper *client, mpd_song *song)
{

    if (currentArtTexture)
    {
        glDeleteTextures(1, &currentArtTexture);
    }
    mpd_album()
    ImMPD::Utils::LoadTextureFromMemory()
}

ImMPD::SimpleAlbumArt::SimpleAlbumArt()
{

}

void ImMPD::SimpleAlbumArt::Draw(MpdClientWrapper *client)
{
    if (ImGui::Begin(GetTitle()))
    {
        //Can we do this?
        if (currentArtTexture)
        {
            //Double cast baybee
            ImGui::Image((ImTextureID)(intptr_t)currentArtTexture, ImGui::GetContentRegionAvail());
        }
    }

    ImGui::End();
}

const char *ImMPD::SimpleAlbumArt::GetTitle()
{
    return "Simple Album Art Viewer";
}

void ImMPD::SimpleAlbumArt::OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data)
{
    if (data->idleEvent == MPD_IDLE_PLAYER)
    {


    }
}

void ImMPD::SimpleAlbumArt::InitState(MpdClientWrapper *client)
{
    PanelBase::InitState(client);
}
