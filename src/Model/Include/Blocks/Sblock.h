#pragma once

#include "AbstractBlock.h"


namespace Tetris::Model::Blocks
{

	/// @brief класс S блок
	class Sblock final : public AbstractBlock
	{
	public:
		/// @brief Конструктор
		/// @param color цвет блока
		Sblock(TypeColor color) : AbstractBlock(color) 
		{
			_stateToPositions = {
				{State::Up, {
				    Position(-1, 0 ), // *  *  *  *
				    Position( 0, 0 ), // *  0  o  *
				    Position( 0, 1 ), // o  o  *  *
				    Position( 1, 1 )  // *  *  *  *
				}},
				{State::Right, {
					Position( 0, 1 ), // o  *  *  *
					Position( 0, 0 ), // o  0  *  *
					Position( 1, 0 ), // *  o  *  *
					Position( 1,-1 )  // *  *  *  *
				}},
				{State::Down, {
					Position(-1, 0 ), // *  o  o  *
					Position( 0, 0 ), // o  0  *  *
					Position( 0,-1 ), // *  *  *  *
					Position(-1,-1 )  // *  *  *  *
				}},
				{State::Left, {
					Position( 0,-1 ), // *  o  *  *
					Position( 0, 0 ), // *  0  o  *
					Position(-1, 0 ), // *  *  o  *
					Position(-1, 1 )  // *  *  *  *
				}}
			};

			_stateToOffset = JLSTZOffset;
		};

		IdShape GetType() const
		{
			return IdShape::Sblock;
		};

	};

} // namespace