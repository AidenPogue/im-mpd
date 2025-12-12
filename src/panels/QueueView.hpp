//
// Created by aiden on 2025-12-10.
//

#ifndef IM_MPD_PLAYLISTVIEW_H
#define IM_MPD_PLAYLISTVIEW_H
#include "PanelBase.hpp"
#include "SongTableColumn.hpp"

namespace ImMPD
{
    class QueueView : public PanelBase
    {
    private:
        std::vector<mpd_song *> currentQueue;
        std::vector<std::vector<std::string>> cellValueCache;
        unsigned currentId;

        void UpdateQueue(MpdClientWrapper *client);

        static void CacheRowIfNeeded(mpd_song *song, const std::vector<SongTableColumn> &columns, std::vector<std::string> &rowCache);
    public:
        QueueView();

        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;

        void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) override;

        void InitState(MpdClientWrapper *client) override;
    };
} // ImMPD

#endif //IM_MPD_PLAYLISTVIEW_H