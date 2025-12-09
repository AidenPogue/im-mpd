#pragma once
#include "../MpdClientWrapper.hpp"

namespace ImMPD
{
    struct PanelBase
    {
        virtual const char *GetTitle() = 0;
        virtual void Draw(MpdClientWrapper *client)= 0;
        virtual ~PanelBase() = 0;
    };
} // namespace ImMPD
