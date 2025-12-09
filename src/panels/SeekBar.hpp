#pragma once

#include "PanelBase.hpp"

namespace ImMPD
{
    class SeekBar : public PanelBase
    {
    public:
        ~SeekBar();
        void Draw(MpdClientWrapper *client) override;
        const char *GetTitle() override;
    };
}
