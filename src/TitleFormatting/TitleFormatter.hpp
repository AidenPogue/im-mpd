#ifndef IM_MPD_TITLEFORMATTER_HPP
#define IM_MPD_TITLEFORMATTER_HPP
#include <optional>
#include <string>
#include <mpd/song.h>

namespace ImpyD::TitleFormatting
{
    std::string FormatSong(mpd_song *song, const std::string &format);

    std::optional<std::string> GetTooFewArgumentsErrorMessage(size_t required, size_t got);

    std::string GetInvalidTagErrorMessage(const std::string &tagName);
}

#endif //IM_MPD_TITLEFORMATTER_HPP