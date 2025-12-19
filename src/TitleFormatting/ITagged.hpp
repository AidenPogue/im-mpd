//
// Created by aiden on 2025-12-16.
//

#ifndef IM_MPD_ITAGGED_HPP
#define IM_MPD_ITAGGED_HPP
#include <memory>
#include <vector>

namespace ImpyD::TitleFormatting
{
    /**
     * Object with an arbitrary number of key value pair metadata tags
     */
    class ITagged
    {
    public:
        virtual ~ITagged() = default;

        virtual const std::string &GetSingleValue(mpd_tag_type key) const = 0;
        virtual const std::vector<std::string> &GetAllValues(mpd_tag_type key) const = 0;
    };
}

#endif //IM_MPD_ITAGGED_HPP