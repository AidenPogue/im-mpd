#include "MpdClientWrapper.hpp"

void MpdClientWrapper::ThrowIfNotConnected()
{
    if (connection == nullptr)
    {
        //Do somethign!
    }
}

MpdClientWrapper::MpdClientWrapper(std::string hostname, uint port)
{
    connection = mpd_connection_new(hostname.c_str(), port, 0);
}

MpdClientWrapper::~MpdClientWrapper()
{
}

mpd_song *MpdClientWrapper::GetCurrentSong()
{
    ThrowIfNotConnected();
    return mpd_run_current_song(connection);
}
