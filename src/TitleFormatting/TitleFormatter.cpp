#include "TitleFormatter.hpp"

#include <iostream>
#include <regex>

#include "BuiltinFormatFunctions.hpp"




namespace ImpyD::TitleFormatting
{
    static const std::regex tagRegex = std::regex("%([a-zA-z]+)%", std::regex_constants::optimize | std::regex_constants::ECMAScript);
    static std::vector<std::string> artistTagListArgs = {"artist", ", "};

    static std::optional<std::string> GetSongTag(mpd_song *song, std::string const &tag)
    {
        if (tag == "duration")
        {

        }

        auto tagType = mpd_tag_name_iparse(tag.c_str());
        if (tagType == MPD_TAG_UNKNOWN)
        {
            return GetInvalidTagErrorMessage(tag);
        }

        if (tagType == MPD_TAG_ARTIST || tagType == MPD_TAG_ARTIST_SORT)
        {
            return BuiltIn::TagList(song, artistTagListArgs);
        }

        //Default to first value.
        auto rawTag =  mpd_song_get_tag(song, tagType, 0);
        return rawTag == nullptr ? "" : rawTag;
    }


    std::string FormatSong(mpd_song *song, const std::string &format)
    {
        auto begin = std::sregex_iterator(format.begin(), format.end(), tagRegex);
        auto end = std::sregex_iterator();
        auto outStr = std::string(format);
        int curOffset = 0;
        for (auto it = begin; it != end; ++it)
        {
            auto const &match = *it;
            auto tagValue = GetSongTag(song, match.str(1));
            if (!tagValue.has_value())
            {
                continue;
            }
            outStr.replace(match.position() + curOffset, match.length(), tagValue.value());
            curOffset += tagValue.value().length() - match.length();
        }
        return outStr;
    }

    static std::string GetErrorString(const std::string &message)
    {
        return "<ERROR: " + message + ">";
    }

    std::optional<std::string> GetTooFewArgumentsErrorMessage(size_t required, size_t got)
    {
        if (got < required)
        {
            return GetErrorString("Expected " + std::to_string(required) + " arguments, got " + std::to_string(got));
        }
        return std::nullopt;
    }

    std::string GetInvalidTagErrorMessage(const std::string &tagName)
    {
        return GetErrorString("'" + tagName + "' is not a valid tag");
    }
}


