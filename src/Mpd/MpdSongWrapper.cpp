#include "MpdSongWrapper.hpp"

#include <stdexcept>

MpdSongWrapper::MpdSongWrapper(mpd_song *song) : song(song)
{
    if (song == nullptr)
    {
        throw std::runtime_error("Song cannot be null.");
    }
}

MpdSongWrapper::~MpdSongWrapper()
{
    if (song != nullptr)
    {
        mpd_song_free(song);
    }
}
