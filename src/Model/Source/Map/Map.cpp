#include "Map/Map.h"


namespace Tetris::Model::Map
{

    Map::Map(size_t x, size_t y):_data(y), _activeShape(nullptr), positionShape(0,0)
    {
        for(auto& row: _data)
            row.resize(x);
    }

} // namespace