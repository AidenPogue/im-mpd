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

        /**
         * Called when any idle event is recieved from the client.
         * @param client The client that produced the idle event.
         * @param data Data for the idle event.
         */
        virtual void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) {}

        /**
         * Called once immediately after creating the panel.
         * @param client The connected client.
         */
        virtual void InitState(MpdClientWrapper *client) {}
    };
} // namespace ImMPD
