#ifndef IM_MPD_MPDIDLEEVENTDATA_HPP
#define IM_MPD_MPDIDLEEVENTDATA_HPP
#include <mpd/idle.h>
#include <mpd/song.h>
#include <mpd/status.h>

//namespace ImpyD::Mpd
//{
    /**
   * Contains the idle event id and some shared data for convenience.
   */
    class MpdIdleEventData
    {
    public:
        const mpd_idle idleEvent;
        mpd_song *currentSong;
        mpd_status *currentStatus;

        MpdIdleEventData(mpd_idle idle_event, mpd_song *current_song, mpd_status *current_status)
            : idleEvent(idle_event),
              currentSong(current_song),
              currentStatus(current_status)
        {
        }

        ~MpdIdleEventData()
        {
            if (currentStatus != nullptr)
            {
                mpd_status_free(currentStatus);
            }
            if (currentSong != nullptr)
            {
                mpd_song_free(currentSong);
            }
        }
    };
//}

#endif //IM_MPD_MPDIDLEEVENTDATA_HPP