#pragma once

#include <Model/Precompile.h>
#include <Model/Export.h>
#include <Model/Forwards.h>

#include <Model/Types.h>


namespace Tetris::Model
{

    /// @brief Описание модели игры
    struct MODEL_EXPORT DescriptionModel
    {
        DescriptionModel(): map(), size({0,0}), nextBlock(nullptr){}
        ~DescriptionModel(){}

        std::vector<TypeColor> map; ///< Игровая карта
        MapSize size;               ///< Размер карты
        AbstractBlockPtr nextBlock{nullptr}; ///< Следующий блок
        std::optional<unsigned int> score; ///< Текущий счет
    };

}