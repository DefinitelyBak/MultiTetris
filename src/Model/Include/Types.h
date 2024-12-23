#pragma once

#include "Precompile.h"
#include "Forwards.h"


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
		int x;
		int y;
	};

    /// @brief Контейнер - описание положения фигуры
    using Positions = std::array<Position, 4>;

    /// @brief Смещения
    using Offsets = std::array<Position, 5>;

    // Операции с Offsets
    Offsets operator+(const Offsets& lhs, const Offsets& rhs);
    Offsets operator-(const Offsets& lhs, const Offsets& rhs);
    bool operator==(const Offsets& lhs, const Offsets& rhs);
    bool operator!=(const Offsets& lhs, const Offsets& rhs);

    // Операции с Position
    Position operator+(const Position& lhs, const Position& rhs);
    Position operator-(const Position& lhs, const Position& rhs);
    bool operator==(const Position& lhs, const Position& rhs);
    bool operator!=(const Position& lhs, const Position& rhs);

    // Операции с Offsets и Position
    Offsets operator+(const Offsets& lhs, const Position& rhs);
    Offsets operator+(const Position& lhs, const Offsets& rhs);
    Offsets operator-(const Offsets& lhs, const Position& rhs);

    // Операции с Positions
    Positions operator+(const Positions& lhs, const Position& rhs);
    Positions operator+(const Position& lhs, const Positions& rhs);
    Positions operator-(const Positions& lhs, const Position& rhs);
} // namespace Tetris::Model
