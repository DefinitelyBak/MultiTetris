#pragma once

#include <Model/Blocks/AbstractBlock.h>


namespace Tetris::Model::Blocks
{
    /// @brief класс O блок
    class MODEL_EXPORT Oblock final : public AbstractBlock
    {
    public:
        /// @brief Конструктор
        /// @param color цвет блока
        Oblock(TypeColor color) : AbstractBlock(color) 
        {
            _orientationToPositions = {
                {Orientation::Up, {
                    Position(0, 1),  // *  o  O 
                    Position(1, 1),  // *  0  O
                    Position(1, 0),  // *  *  *
                    Position(0, 0)
                }},
                {Orientation::Right, {
                    Position(1, 0),  // *  *  *  
                    Position(1, -1), // *  0  o  
                    Position(0, -1), // *  o  o  
                    Position(0, 0)
                }},
                {Orientation::Down, {
                    Position(0, -1), // *  *  *
                    Position(-1, -1), // o  0  *
                    Position(-1, 0),  // o  o  *
                    Position(0, 0)
                }},
                {Orientation::Left, {
                    Position(0, 1),  // o  o  *
                    Position(-1, 1), // o  0  *
                    Position(-1, 0), // *  *  *
                    Position(0, 0)
                }}
            };

            _orientationToOffset = OOffset;
        }

        /// @brief Получение типа блока
        /// @return Идентификатор формы блока
        [[nodiscard]] TypeBlock GetType() const override
        {
            return TypeBlock::Oblock;
        }
    };

} // namespace Tetris::Model::Blocks
