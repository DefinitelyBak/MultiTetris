#pragma once

#include "Color.h"


namespace Tetris::Common::Data
{
    /// @brief Описание поля карты
    struct Field
    {
        Field(Color color = Color::None, int x = 0, int y = 0):
            color{color}, x{x}, y{y} {};
          
        Color color {Color::None};
        int x {0};
        int y {0};
    };

} // namespace