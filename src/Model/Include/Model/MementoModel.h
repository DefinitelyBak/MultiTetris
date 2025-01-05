#pragma once

#include <Model/Precompile.h>
#include <Model/Export.h>
#include <Model/Forwards.h>

#include <Model/Types.h>


namespace Tetris::Model
{

    /// @brief Снимок модели игры
    struct MODEL_EXPORT MementoModel
    {
        std::vector<TypeColor> map; ///< Игровая карта
        MapSize size{0,0};          ///< Размер карты
        AbstractBlockPtr nextBlock{nullptr}; ///< Следующий блок
        unsigned int score{0}; ///< Текущий счет
    };

}