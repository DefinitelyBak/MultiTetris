#pragma once

#include "AbstractBlock.h"


namespace Tetris::Model::Blocks
{

	/// @brief класс O блок
	class Oblock final : public AbstractBlock
	{
	public:
		/// @brief Конструктор
		/// @param color цвет блока
		Oblock(TypeColor color) : AbstractBlock(color) 
		{
			_stateToPositions = {
				{State::Up, {
				    Position( 0, 1 ), // *  o  O 
				    Position( 1, 1 ), // *  0  O
				    Position( 1, 0 ), // *  *  *
				    Position( 0, 0 )
				}},
				{State::Right, {
				    Position( 1, 0 ), // *  *  *  
				    Position( 1,-1 ), // *  0  o  
				    Position( 0,-1 ), // *  o  o  
				    Position( 0, 0 )
				}},
				{State::Down, {
				    Position( 0,-1 ), // *  *  *
				    Position(-1,-1 ), // o  0  *
				    Position(-1, 0 ), // o  o  *
				    Position( 0, 0 )
				}},
				{State::Left, {
				    Position( 0, 1 ), // o  o  *
				    Position(-1, 1 ), // o  0  *
				    Position(-1, 0 ), // *  *  *
				    Position( 0, 0 )
				}}
			};

			_stateToOffset = OOffset;
		};

		IdShape GetType() const
		{
			return IdShape::Oblock;
		};

	};

} // namespace