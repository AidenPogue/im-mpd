//
// Created by aiden on 2025-12-11.
//

#include "BuiltinFormatFunctions.hpp"

#include "TitleFormatter.hpp"

std::string ImpyD::TitleFormatting::BuiltIn::TagList(const ITagged & tagged, std::vector<std::string> &args)
{
    auto err = GetTooFewArgumentsErrorMessage(2, args.size());
    if (err) return err.value();

    auto tagType = mpd_tag_name_iparse(args[0].c_str());
    if (tagType == MPD_TAG_UNKNOWN)
    {
        return GetInvalidTagErrorMessage(args[0]);
    }

    auto outString = std::string();
    const auto &values = tagged.GetAllValues(tagType);

    for (int i = 0; i < values.size(); ++i)
    {
        if (i != 0)
        {
            outString += args[1];
        }

        outString += values[i];
    }

    return std::move(outString);
}
