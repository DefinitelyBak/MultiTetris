#pragma once

#include "AbstractBlock.h"


namespace Tetris::Model::Blocks
{

	/// @brief класс O блок
	class Oblock : public AbstractBlock
	{
	public:
		/// @brief Конструктор
		/// @param color цвет блока
		Oblock(Common::Data::Color color) : AbstractBlock(color) 
		{
			_positionToDescription = {
				{State::Up, {
				    PosotionFiel( 0, 1 ), // o  o  * 
				    PosotionFiel( 0, 0 ), // o  0  *
				    PosotionFiel( 1, 0 ), // *  *  *
				    PosotionFiel( 1, 1 )
				}},
				{State::Right, {
				    PosotionFiel( 0, 1 ), // o  o  *  
				    PosotionFiel( 0, 0 ), // o  0  *  
				    PosotionFiel( 1, 0 ), // *  *  *  
				    PosotionFiel( 1, 1 )
				}},
				{State::Down, {
				    PosotionFiel( 0, 1 ), // o  o  *
				    PosotionFiel( 0, 0 ), // o  0  *
				    PosotionFiel( 1, 0 ), // *  *  *
				    PosotionFiel( 1, 1 )
				}},
				{State::Left, {
				    PosotionFiel( 0, 1 ), // o  o  *
				    PosotionFiel( 0, 0 ), // o  0  *
				    PosotionFiel( 1, 0 ), // *  *  *
				    PosotionFiel( 1, 1 )
				}}
			};

		};

	};

} // namespace