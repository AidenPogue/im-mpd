#pragma once
#include "../MpdClientWrapper.hpp"

namespace ImMPD
{
    class PanelBase
    {
    public:
        virtual const char *GetTitle() = 0;
        virtual void Draw(MpdClientWrapper *client)= 0;
        virtual ~PanelBase() = 0;

        //Client events
        virtual void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) {}
    };
} // namespace ImMPD
