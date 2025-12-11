//
// Created by aiden on 2025-12-10.
//

#ifndef IM_MPD_PLAYLISTVIEW_H
#define IM_MPD_PLAYLISTVIEW_H
#include "PanelBase.hpp"

namespace ImMPD
{
    class PlaylistView : public PanelBase
    {
    private:
        std::vector<mpd_song *> currentPlaylist;

        void GetPlaylist(MpdClientWrapper *client);
    public:
        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;

        void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) override;

        void InitState(MpdClientWrapper *client) override;

        PlaylistView();
    };
} // ImMPD

#endif //IM_MPD_PLAYLISTVIEW_H