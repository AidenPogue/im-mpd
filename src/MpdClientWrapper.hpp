#pragma once

#include <functional>
#include <list>
#include <string>
#include <mpd/client.h>
#include <mpd/async.h>

struct MpdPlayInfo
{
    bool isPlaying;
    double startedAtGlfwTime;
    float startedAtElapsedSeconds;
};


/**
 * Contains the idle event id and some shared data for convinence.
 */
//MOVE INTO OWN FILE!
class MpdIdleEventData
{
public:
    mpd_idle idleEvent;
    mpd_song *currentSong;
    mpd_status *currentStatus;

    void Free()
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

class MpdClientWrapper
{
private:
    const char *hostname;
    uint port;

    bool noIdleMode;

    mpd_connection *connection = nullptr;

    std::list<std::function<void(MpdClientWrapper*, MpdIdleEventData*)>> listeners;

    void ThrowIfNotConnected();
    void HandleIdle(mpd_idle idle);
    int Connect();
    bool ReceiveIdle();
    bool ReceiveSongList(std::vector<mpd_song *> &songList);

public:
    MpdClientWrapper(const char *hostname, uint port, unsigned binaryLimit = 8192);
    ~MpdClientWrapper();

    bool GetIsConnected();
    void AddIdleListener(std::function<void(MpdClientWrapper*, MpdIdleEventData*)> listener);


    /**
     * Sends the noidle command to MPD. Call this before sending commands *outside of an event handler*
     */
    void BeginNoIdle();
    void EndNoIdle();

    mpd_song *GetCurrentSong();
    bool GetQueue(std::vector<mpd_song *> &songList);
    mpd_status *GetStatus();
    //bool StartAlbumArt(const char *uri, )

    //Db

    
    //Playback

    bool PlayCurrent();
    bool PlayId(unsigned id);
    bool Pause();
    bool Toggle();
    bool Next();
    bool Prev();
    bool SeekToSeconds(float s, bool relative);

    bool SetVolume(int volume);
    bool ChangeVolume(int by);

   

    void Poll();
};