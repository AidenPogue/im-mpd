#include "SimpleAlbumArt.hpp"
#include "imgui.h"


void ImMPD::SimpleAlbumArt::Draw(MpdClientWrapper *client)
{
    if (ImGui::Begin(GetTitle()))
    {
        
    }

    ImGui::End();
}

const char *ImMPD::SimpleAlbumArt::GetTitle()
{
    return "Simple Album Art Viewer";
}
