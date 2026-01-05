#include "ArbitraryTagged.hpp"

void ImpyD::Mpd::ArbitraryTagged::AddValue(mpd_tag_type key, std::string value)
{
    if (!map.contains(key))
    {
        map.emplace(key, std::vector<std::string>());
    }

    map[key].push_back(value);
}

std::string ImpyD::Mpd::ArbitraryTagged::GetSingleValue(mpd_tag_type key) const
{
    if (!map.contains(key))
    {
        return "";
    }

    return map.at(key).front();
}

std::vector<std::string> ImpyD::Mpd::ArbitraryTagged::GetAllValues(mpd_tag_type key) const
{
    if (!map.contains(key))
    {
        return {};
    }

    return map.at(key);
}

std::vector<ImpyD::Mpd::TagFilterGenerator> ImpyD::Mpd::ArbitraryTagged::GetFilters() const
{
    std::vector<TagFilterGenerator> result;

    //We'll have at least one filter per tag type, and most tags will only have one value.
    result.reserve(map.size());

    for (const auto &pair : map)
    {
        for (const auto &value : pair.second)
        {
            result.emplace_back(pair.first, value);
        }
    }

    return result;
}