#pragma once

#include "Precompile.h"

#include "Forwards.h"
#include "Types.h"


namespace Tetris::Model
{

    /// @brief Описание модели игры
    struct DescriptionModel
    {
        DescriptionModel(): map(), size({0,0}), nextBlock(nullptr){}
        ~DescriptionModel(){}

        std::vector<TypeColor> map; ///< Игровая карта
        MapSize size;               ///< Размер карты
        AbstractBlockPtr nextBlock{nullptr}; ///< Следующий блок
        std::optional<unsigned int> score; ///< Текущий счет
    };

}