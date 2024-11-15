#pragma once

#include "Precompile.h"


/// @brief Типы используемые в  
namespace Tetris::Model
{
	
	/// @brief 
	enum class Command: int
	{
		Right,
		Left,
		Down,
		RotateRight,
		RotateLeft
	};

    /// @brief Цвет поля карты
    enum class Color: int
    {
        None,
        Red,
        Green,
        Yellow,
        Blue,
        Orange
    };

    using DataMap = std::vector<Color>;

    /// @brief 
    struct MapSize
	{
		size_t columns;
		size_t rows;
	};

	/// @brief Координаты поля фигры относительно центра фигуры, координаты x, y
	using Position = std::pair<int, int>;

	/// @brief Контейнер - описание положение фигуры
	using Positions = std::array<Position, 4>;

	/// @brief 
	using Offsets = std::array<Position, 5>;

	/// Операции с типами
	Offsets operator+(const Offsets& lhs, const Offsets& rhs);
	Offsets operator-(const Offsets& lhs, const Offsets& rhs);

	bool operator==(const Offsets& lhs, const Offsets& rhs);
	bool operator!=(const Offsets& lhs, const Offsets& rhs);

	Position operator+(const Position& lhs, const Position& rhs);
	Position operator-(const Position& lhs, const Position& rhs);

	bool operator==(const Position& lhs, const Position& rhs);
	bool operator!=(const Position& lhs, const Position& rhs);

	Offsets operator+(const Offsets& lhs, const Position& rhs);
	Offsets operator+(const Position& lhs, const Offsets& rhs);
	Offsets operator-(const Offsets& lhs, const Position& rhs);

	Positions operator+(const Positions& lhs, const Position& rhs);
	Positions operator+(const Position& lhs, const Positions& rhs);
	Positions operator-(const Positions& lhs, const Position& rhs);

}