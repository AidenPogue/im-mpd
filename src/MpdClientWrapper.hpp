#pragma once

#include <string>
#include <mpd/client.h>
#include <mpd/async.h>

struct MpdPlayInfo
{
    bool isPlaying;
    double startedAtGlfwTime;
    float startedAtElapsedSeconds;
};

class MpdClientWrapper
{
private:
    const char *hostname;
    uint port;

    mpd_connection *connection;
    mpd_connection *idleConnection;

    mpd_song *currentSong = nullptr;
    MpdPlayInfo playInfo;

    void ThrowIfNotConnected();
    void HandleEvents(mpd_idle idle);
    int Connect();

public:
    MpdClientWrapper(const char *hostname, uint port);
    ~MpdClientWrapper();

    mpd_song *GetCurrentSong();
    mpd_status *GetStatus();
    
    MpdPlayInfo GetCurrentPlayInfo();
    
    //Playback
    bool Play();
    bool Pause();
    bool Toggle();
    bool Next();
    bool Prev();
    bool SeekToSeconds(float s, bool relative);


   

    void Poll();
};