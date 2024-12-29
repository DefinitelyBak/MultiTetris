#pragma once

#include <Model/Blocks/AbstractBlock.h>


namespace Tetris::Model::Blocks
{
    /// @brief класс L блок
    class MODEL_EXPORT Lblock final : public AbstractBlock
    {
    public:
        /// @brief Конструктор
        /// @param color цвет блока
        Lblock(TypeColor color) : AbstractBlock(color) 
        {
            _stateToPositions = {
                {State::Up,
                    {
                        Position(1, 1),  // *  *  o
                        Position(1, 0),  // o  0  o
                        Position(0, 0),  // *  *  *
                        Position(-1, 0)
                    }
                },
                {State::Right,
                    {
                        Position(1, -1), // *  o  *
                        Position(0, -1), // *  0  *
                        Position(0, 0),  // *  o  o
                        Position(0, 1)
                    }
                },
                {State::Down,
                    {
                        Position(-1, -1), // *  *  *
                        Position(-1, 0),  // o  0  o
                        Position(0, 0),   // o  *  *
                        Position(1, 0)
                    }
                },
                {State::Left,
                    {
                        Position(-1, 1),  // o  o  *
                        Position(0, 1),   // *  0  *
                        Position(0, 0),   // *  o  *
                        Position(0, -1)
                    }
                }
            };

            _stateToOffset = JLSTZOffset;
        }

		/// @brief Получение типа блока
		/// @return Идентификатор формы блока
        TypeBlock GetType() const override
        {
            return TypeBlock::Lblock;
        }
    };

} // namespace Tetris::Model::Blocks
