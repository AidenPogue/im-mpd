//
// Created by aiden on 2025-12-09.
//

#include "LibraryTreeView.h"

namespace ImMPD
{
    const char * LibraryTreeView::GetTitle()
    {
        return "Library Tree View";
    }

    void LibraryTreeView::Draw(MpdClientWrapper *client)
    {
    }

    void LibraryTreeView::OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data)
    {
        PanelBase::OnIdleEvent(client, data);
    }

    void LibraryTreeView::InitState(MpdClientWrapper *client)
    {

    }
} // ImMPD