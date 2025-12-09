#include "MpdClientWrapper.hpp"
#include <iostream>
#include <poll.h>
#include <mpd/status.h>
#include <GLFW/glfw3.h>

void MpdClientWrapper::ThrowIfNotConnected()
{
    if (connection == nullptr)
    {
        throw 67;
    }
}

void MpdClientWrapper::HandleEvents(mpd_idle idle)
{
    //Reused for all events.
    static MpdIdleEventData eventData;

    eventData.idleEvent = idle;
    eventData.currentSong = GetCurrentSong();
    eventData.currentStatus = GetStatus();

    for (const auto &listener : listeners)
    {
        if (!listener)
        {
            continue;
        }

        listener(this, &eventData);
    }

    // playInfo.isPlaying = mpd_status_get_state(status) == MPD_STATE_PLAY;
    // playInfo.startedAtElapsedSeconds = mpd_status_get_elapsed_ms(status) / 1000.0f;
    // playInfo.startedAtGlfwTime = glfwGetTime();

    mpd_status_free(eventData.currentStatus);
    mpd_song_free(eventData.currentSong);

    if (idle & MPD_IDLE_PLAYER)
    {

    }
}

int MpdClientWrapper::Connect()
{
    if (connection == nullptr)
    {
        connection = mpd_connection_new(hostname, port, 0);
        idleConnection = mpd_connection_new(hostname, port, 0);
        mpd_send_idle(idleConnection);
        return 0;
    }

    return 1;
}

MpdClientWrapper::MpdClientWrapper(const char* hostname, uint port)
{
    this->hostname = hostname;
    this->port = port;

    listeners = std::list<std::function<void(MpdClientWrapper*, MpdIdleEventData*)>>(8);

    Connect();

}

MpdClientWrapper::~MpdClientWrapper()
{
}

void MpdClientWrapper::AddIdleListener(std::function<void(MpdClientWrapper *, MpdIdleEventData *)> listener)
{
    listeners.push_back(listener);
}

mpd_song *MpdClientWrapper::GetCurrentSong()
{
    ThrowIfNotConnected();
    return mpd_run_current_song(connection);
}

bool MpdClientWrapper::Play()
{
    ThrowIfNotConnected();
    return mpd_run_play(connection);
}

bool MpdClientWrapper::Pause()
{
    ThrowIfNotConnected();
    return mpd_run_pause(connection, true);
}

bool MpdClientWrapper::Toggle()
{
    ThrowIfNotConnected();
    auto status = GetStatus();
    auto state = mpd_status_get_state(status);
    mpd_status_free(status);

    if (state == MPD_STATE_STOP || state == MPD_STATE_UNKNOWN)
    {
        return Play();
    }
    else
    {
        return mpd_run_pause(connection, state != MPD_STATE_PAUSE);
    }
}

bool MpdClientWrapper::Next()
{
    ThrowIfNotConnected();
    return mpd_run_next(connection);
}

bool MpdClientWrapper::Prev()
{
    ThrowIfNotConnected();
    return mpd_run_previous(connection);
}

bool MpdClientWrapper::SeekToSeconds(float s, bool relative)
{
    ThrowIfNotConnected();
    return mpd_run_seek_current(connection, s, relative);
}

bool MpdClientWrapper::SetVolume(int volume)
{
    ThrowIfNotConnected();
    return mpd_run_set_volume(connection, volume);
}

mpd_status *MpdClientWrapper::GetStatus()
{
    return mpd_run_status(connection);
}

void MpdClientWrapper::Poll()
{
    ThrowIfNotConnected();
    struct pollfd pfd;
    pfd.fd = mpd_connection_get_fd(idleConnection);
    pfd.events = POLLIN;   // data available to read
    pfd.revents = 0;

    int ret = poll(&pfd, 1, 0);

    if (ret > 0 && (pfd.revents & (POLLIN | POLLERR | POLLHUP)))
    {
        mpd_idle idle = mpd_recv_idle(idleConnection, false);
        std::cout << mpd_idle_name(idle) << std::endl;
        HandleEvents(idle);
        mpd_send_idle(idleConnection);
    }
}
