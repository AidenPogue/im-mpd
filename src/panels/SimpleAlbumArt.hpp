#pragma once

#include "PanelBase.hpp"
#include "backends/imgui_impl_opengl3_loader.h"

namespace ImMPD
{
    class SimpleAlbumArt : public PanelBase
    {
    private:
        GLuint currentArtTexture = 0;
        uint8_t *receiveBuffer = NULL;

        void LoadArtTexture(MpdClientWrapper *client, mpd_song *song);

    public:
        SimpleAlbumArt();
        void Draw(MpdClientWrapper *client) override;
        const char *GetTitle() override;

        void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) override;

        void InitState(MpdClientWrapper *client) override;
    };
}
