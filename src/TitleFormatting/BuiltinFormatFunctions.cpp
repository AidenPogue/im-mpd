//
// Created by aiden on 2025-12-11.
//

#include "BuiltinFormatFunctions.hpp"

#include "TitleFormatter.hpp"

std::string ImMPD::TitleFormatting::BuiltIn::TagList(const mpd_song *song, std::vector<std::string> &args)
{
    auto err = GetTooFewArgumentsErrorMessage(2, args.size());
    if (err) return err.value();

    auto tagType = mpd_tag_name_iparse(args[0].c_str());
    if (tagType == MPD_TAG_UNKNOWN)
    {
        return GetInvalidTagErrorMessage(args[0]);
    }

    auto outString = std::string();
    size_t idx = 0;
    const char *value = mpd_song_get_tag(song, tagType, idx);
    while (value != nullptr)
    {
        if (idx != 0)
        {
            outString += args[1];
        }
        outString += value;
        value = mpd_song_get_tag(song, tagType, ++idx);
    }

    return outString;
}
