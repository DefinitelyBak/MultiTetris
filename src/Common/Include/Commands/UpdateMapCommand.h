#pragma once

#include "Precompile.h"

#include "AbstractCommand.h"
#include "Data/Types.h"


namespace Tetris::Common
{
    /// @brief 
    class UpdateMapCommand:public AbstractCommand
    {
    public:

        /// @brief 
        /// @param map 
        /// @param size 
        /// @param type 
        UpdateMapCommand(Data::MapPtr map, Data::MapSize size, CommonType type = CommonType::UpdateMap);

        /// @brief 
        /// @return 
        std::pair<Data::MapPtr, Data::MapSize> GetData() const;

    private:
        /// @brief 
        Data::MapPtr _map;

        /// @brief 
        Data::MapSize _size;
    };

}