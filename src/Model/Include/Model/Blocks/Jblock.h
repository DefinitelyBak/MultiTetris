#pragma once

#include <Model/Blocks/AbstractBlock.h>


// I, J, L, O, S, T, Z Блоки и их описания
namespace Tetris::Model::Blocks
{
    /// @brief класс J блок
    class MODEL_EXPORT Jblock final : public AbstractBlock
    {
    public:
        /// @brief Конструктор
        /// @param color цвет блока
        Jblock(TypeColor color) : AbstractBlock(color) 
        {
            _orientationToPositions = {
                {Orientation::Up, 
                    {
                        Position(-1, 1), // o  *  *
                        Position(-1, 0), // o  0  o
                        Position(0, 0),  // *  *  *
                        Position(1, 0)
                    }
                },
                {Orientation::Right,
                    {
                        Position(1, 1),  // *  o  o
                        Position(0, 1),  // *  0  *
                        Position(0, 0),  // *  o  *
                        Position(0, -1)
                    }
                },
                {Orientation::Down,
                    {
                        Position(1, -1), // *  *  *
                        Position(1, 0),  // o  0  o
                        Position(0, 0),  // *  *  o
                        Position(-1, 0)
                    }
                },
                {Orientation::Left,
                    {
                        Position(-1, -1), // *  o  *
                        Position(0, -1),  // *  0  *
                        Position(0, 0),   // o  o  *
                        Position(0, 1)
                    }
                }
            };

            _orientationToOffset = JLSTZOffset;
        }

		/// @brief Получение типа блока
		/// @return Идентификатор формы блока
        [[nodiscard]] TypeBlock GetType() const override
        {
            return TypeBlock::Jblock;
        }
    };

} // namespace Tetris::Model::Blocks