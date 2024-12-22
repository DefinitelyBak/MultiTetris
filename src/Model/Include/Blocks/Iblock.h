#pragma once

#include "AbstractBlock.h"


// I, J, L, O, S, T, Z Блоки и их описания
namespace Tetris::Model::Blocks
{

    /// @brief класс I блок
    class Iblock final : public AbstractBlock
    {
    public:
        /// @brief Конструктор
        /// @param color цвет блока
        Iblock(TypeColor color) : AbstractBlock(color)
        {
            _stateToPositions = {
                {State::Up,
                    {
                        Position(-1, 0), // *  *  *  *  *
                        Position( 0, 0), // *  *  *  *  *
                        Position( 1, 0), // *  о  0  о  о
                        Position( 2, 0)     // *  *  *  *  *
                    }                     // *  *  *  *  *
                },
                {State::Right,
                    {
                        Position(0, 1), // *  *  *  *  *
                        Position(0, 0), // *  *  о  *  *
                        Position(0,-1), // *  *  0  *  *
                        Position(0,-2)  // *  *  о  *  *
                    }                    // *  *  о  *  *
                },                       
                {State::Down,
                    {
                        Position( 1, 0), // *  *  *  *  *
                        Position( 0, 0), // *  *  *  *  *
                        Position(-1, 0), // о  о  0  о  *
                        Position(-2, 0)  // *  *  *  *  *
                    }                     // *  *  *  *  *
                },                         
                {State::Left,
                    {
                        Position( 0,-1), // *  *  о  *  *
                        Position( 0, 0), // *  *  о  *  *
                        Position( 0, 1), // *  *  0  *  *
                        Position( 0, 2)  // *  *  о  *  *
                    }                     // *  *  *  *  *
                } 
            };

            _stateToOffset = IOffset;
        };

        /// @brief Получение типа блока
        /// @return Идентификатор формы блока
        TypeBlock GetType() const
        {
            return TypeBlock::Iblock;
        };
    };

} // namespace Tetris::Model::Blocks
