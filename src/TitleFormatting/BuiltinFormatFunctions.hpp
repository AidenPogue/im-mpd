#ifndef IM_MPD_BUILTINFORMATFUNCTIONS_HPP
#define IM_MPD_BUILTINFORMATFUNCTIONS_HPP
#include <string>
#include <vector>
#include <mpd/song.h>


namespace ImMPD::TitleFormatting::BuiltIn
{

    /**
     * Formats a string of concatenated tag values with a separator for tags with multiple values.
     * @param song
     * @param args [0] = tag name, [1] = separator
     * @return
     */
    std::string TagList(const mpd_song *song, std::vector<std::string> &args);
}
#endif //IM_MPD_BUILTINFORMATFUNCTIONS_HPP