#pragma once

#include "Precompile.h"


/// @brief Типы используемые в  
namespace Tetris::Model
{
	
    /// @brief Состояние фигуры
	enum class State: int
	{
		Up = 1,
		Right,
		Down,
		Left
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