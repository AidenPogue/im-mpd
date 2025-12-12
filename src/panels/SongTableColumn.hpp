#ifndef IM_MPD_SONGTABLECOLUMN_HPP
#define IM_MPD_SONGTABLECOLUMN_HPP
#include <string>

class SongTableColumn
{
public:
    const std::string id, displayName, format;
    SongTableColumn( std::string id,  std::string displayName,  std::string format);
};

#endif //IM_MPD_SONGTABLECOLUMN_HPP