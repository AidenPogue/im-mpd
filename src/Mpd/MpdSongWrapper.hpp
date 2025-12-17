#include <mpd/song.h>

#ifndef IM_MPD_MPDSONGWRAPPER_HPP
#define IM_MPD_MPDSONGWRAPPER_HPP

//Manages the lifetime of a mpd_song and provides some utility methods.
class MpdSongWrapper
{
private:
    mpd_song *song = nullptr;
public:
    MpdSongWrapper(mpd_song *song);
    ~MpdSongWrapper();
};


#endif //IM_MPD_MPDSONGWRAPPER_HPP