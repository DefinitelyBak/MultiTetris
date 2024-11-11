#pragma once

#include "Precompile.h"

#include "Color.h"


namespace Tetris::Common::Data
{
    /// @brief 
    using MapPtr = std::shared_ptr<std::vector<Data::Color>>;

    /// @brief 
    using MapSize = std::pair<size_t, size_t>;
}