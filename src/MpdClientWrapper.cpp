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
    if (idle & MPD_IDLE_PLAYER)
    {
        currentSong = mpd_run_current_song(idleConnection);
        auto status = GetStatus();

        playInfo.isPlaying = mpd_status_get_state(status) == MPD_STATE_PLAY;
        playInfo.startedAtElapsedSeconds = mpd_status_get_elapsed_ms(status) / 1000.0f;
        playInfo.startedAtGlfwTime = glfwGetTime();

        mpd_status_free(status);
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
    
    Connect();

}

MpdClientWrapper::~MpdClientWrapper()
{
}

mpd_song *MpdClientWrapper::GetCurrentSong()
{
    ThrowIfNotConnected();
    return currentSong;
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
    return mpd_run_toggle_pause(connection);
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
    return mpd_run_seek_current(connection, s, relative);
}

mpd_status *MpdClientWrapper::GetStatus()
{
    return mpd_run_status(connection);
}

MpdPlayInfo MpdClientWrapper::GetCurrentPlayInfo()
{
    return playInfo;
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
