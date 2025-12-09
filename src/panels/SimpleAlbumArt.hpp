#pragma once

#include "PanelBase.hpp"

namespace ImMPD
{
    class SimpleAlbumArt : public PanelBase
    {
    private:
        float currentSeekSeconds;
    public:
        ~SimpleAlbumArt();
        void Draw(MpdClientWrapper *client) override;
        const char *GetTitle() override;
    };
}
