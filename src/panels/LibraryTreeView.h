//
// Created by aiden on 2025-12-09.
//

#ifndef IM_MPD_LIBRARYTREEVIEW_H
#define IM_MPD_LIBRARYTREEVIEW_H
#include "PanelBase.hpp"

namespace ImMPD
{
    class LibraryTreeView : public PanelBase
    {
    public:
        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;

        void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) override;

        void InitState(MpdClientWrapper *client) override;
    };
} // ImMPD

#endif //IM_MPD_LIBRARYTREEVIEW_H