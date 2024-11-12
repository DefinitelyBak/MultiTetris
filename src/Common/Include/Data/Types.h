#pragma once

#include "Precompile.h"


namespace Tetris::Common::Data
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

    using Map = std::vector<Data::Color>;

    /// @brief 
    using MapPtr = std::shared_ptr<Map>;

    /// @brief 
    using MapSize = std::pair<size_t, size_t>;
}