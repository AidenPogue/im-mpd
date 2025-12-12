#include "SongTableColumn.hpp"

#include <utility>

SongTableColumn::SongTableColumn(std::string id, std::string displayName, std::string format) :
    id(std::move(id)),
    displayName(std::move(displayName)),
    format(std::move(format))
{
}
