#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include <Model/Export.h>


namespace Tetris::Model
{
    /// @brief Типы используемые в Tetris

    /// @brief Типы блоков
    enum class TypeBlock : int 
    {
        None,
        Iblock,
        Jblock,
        Lblock,
        Oblock,
        Sblock,
        Tblock,
        Zblock
    };

    /// @brief Команды управления
    enum class Command : int
    {
        Right,
        Left,
        Down,
        RotateRight,
        RotateLeft
    };

    /// @brief Цвета поля карты
    enum class TypeColor : int
    {
        None,
        Red,
        Green,
        Yellow,
        Blue
    };

    /// @brief Размер карты
    struct MapSize
    {
        size_t columns; ///< Количество колонок
        size_t rows;    ///< Количество строк
    };

    /// @brief Координаты фигуры относительно центра
    struct Position
	{
		size_t x;
		size_t y;
	};

    /// @brief Контейнер - описание положения фигуры
    using Positions = std::array<Position, 4>;

    /// @brief Смещения
    using Offsets = std::array<Position, 5>;

    // Операции с Offsets
    MODEL_EXPORT Offsets operator+(const Offsets& lhs, const Offsets& rhs);
    MODEL_EXPORT Offsets operator-(const Offsets& lhs, const Offsets& rhs);
    MODEL_EXPORT bool operator==(const Offsets& lhs, const Offsets& rhs);
    MODEL_EXPORT bool operator!=(const Offsets& lhs, const Offsets& rhs);

    // Операции с Position
    MODEL_EXPORT Position operator+(const Position& lhs, const Position& rhs);
    MODEL_EXPORT Position operator-(const Position& lhs, const Position& rhs);
    MODEL_EXPORT bool operator==(const Position& lhs, const Position& rhs);
    MODEL_EXPORT bool operator!=(const Position& lhs, const Position& rhs);

    // Операции с Offsets и Position
    MODEL_EXPORT Offsets operator+(const Offsets& lhs, const Position& rhs);
    MODEL_EXPORT Offsets operator+(const Position& lhs, const Offsets& rhs);
    MODEL_EXPORT Offsets operator-(const Offsets& lhs, const Position& rhs);

    // Операции с Positions
    MODEL_EXPORT Positions operator+(const Positions& lhs, const Position& rhs);
    MODEL_EXPORT Positions operator+(const Position& lhs, const Positions& rhs);
    MODEL_EXPORT Positions operator-(const Positions& lhs, const Position& rhs);
} // namespace Tetris::Model
