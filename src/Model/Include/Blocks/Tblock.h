#pragma once

#include "AbstractBlock.h"


namespace Tetris::Model::Blocks
{

	/// @brief класс T блок
	class Tblock : public AbstractBlock
	{
	public:
		/// @brief Конструктор
		/// @param color цвет блока
		Tblock(Common::Data::Color color) : AbstractBlock(color) 
		{
			// (1, 0) -> (0, -1) -> (-1, 0) -> (0, 1)
			_positionToDescription = {
				{State::Up, {
				    PosotionFiel( 1, 0 ),  // *  *  *
				    PosotionFiel( 0, 0 ),  // o  0  o
				    PosotionFiel( 0,-1 ),  // *  o  *
				    PosotionFiel(-1, 0 )   
				}},
				{State::Right, {
				    PosotionFiel( 0,-1 ),  // *  o  *
				    PosotionFiel( 0, 0 ),  // o  0  *
				    PosotionFiel(-1, 0 ),  // *  o  *
				    PosotionFiel( 0, 1 ) 
				}},
				{State::Down, {
				    PosotionFiel(-1, 0 ),  // *  o  *
				    PosotionFiel( 0, 0 ),  // o  0  o
				    PosotionFiel( 0, 1 ),  // *  *  *
				    PosotionFiel( 1, 0 ) 
				}},
				{State::Left, {
				    PosotionFiel( 0, 1 ),  // *  o  *
				    PosotionFiel( 0, 0 ),  // *  0  o
				    PosotionFiel( 1, 0 ),  // *  o  *
				    PosotionFiel( 0,-1 )   
				}}  
			};

		};

	};

} // namespace