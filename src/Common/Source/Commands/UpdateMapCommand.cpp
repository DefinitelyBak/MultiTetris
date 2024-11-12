#include "Commands/UpdateMapCommand.h"


namespace Tetris::Common
{

    UpdateMapCommand::UpdateMapCommand(Data::MapPtr map, Data::MapSize size): AbstractCommand(CommonType::UpdateMap), _map(map), _size(size)
    {}

    std::pair<Data::MapPtr, Data::MapSize> UpdateMapCommand::GetData() const
    {
        return std::pair<Data::MapPtr, Data::MapSize>(_map, _size);
    }

}