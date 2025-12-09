#pragma once

#include "PanelBase.hpp"
#include "../MpdClientWrapper.hpp"

namespace ImMPD
{
    class PlaybackButtonsPanel : public PanelBase
    {
    private:
    public:
        ~PlaybackButtonsPanel();

        void Draw(MpdClientWrapper *client) override;
        const char *GetTitle() override;
    };
}