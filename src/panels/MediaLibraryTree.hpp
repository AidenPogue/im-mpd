//
// Created by aiden on 2025-12-08.
//

#ifndef IM_MPD_MEDIALIBRARYTREE_H
#define IM_MPD_MEDIALIBRARYTREE_H
#include "PanelBase.hpp"
#include "mpd/database.h"

namespace ImMPD
{
    class MediaLibraryTree : public PanelBase
    {
    private:


    public:
        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;

        ~MediaLibraryTree() override;
    };
} // ImMPD

#endif //IM_MPD_MEDIALIBRARYTREE_H