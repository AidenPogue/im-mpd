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
struct MpdIdleEventData
{
    mpd_idle idleEvent;
    mpd_song *currentSong;
    mpd_status *currentStatus;
};

class MpdClientWrapper
{
private:
    const char *hostname;
    uint port;

    mpd_connection *connection;
    mpd_connection *idleConnection;

    std::list<std::function<void(MpdClientWrapper*, MpdIdleEventData*)>> listeners;

    void ThrowIfNotConnected();
    void HandleEvents(mpd_idle idle);
    int Connect();

public:
    MpdClientWrapper(const char *hostname, uint port);
    ~MpdClientWrapper();

    void AddIdleListener(std::function<void(MpdClientWrapper*, MpdIdleEventData*)> listener);

    mpd_song *GetCurrentSong();
    mpd_status *GetStatus();
    
    //Playback
    bool Play();
    bool Pause();
    bool Toggle();
    bool Next();
    bool Prev();
    bool SeekToSeconds(float s, bool relative);

    bool SetVolume(int volume);

   

    void Poll();
};