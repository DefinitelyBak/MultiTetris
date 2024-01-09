#pragma once

#include "AbstractBlock.h"


//I, J, L, O, S, T, Z Блоки и их описания
namespace Tetris::Model::Blocks
{

	/// @brief класс I блок
	class Iblock : public AbstractBlock
	{
	public:
		/// @brief Конструктор
		/// @param color цвет блока
		Iblock(Common::Data::Color color) : AbstractBlock(color) 
		{
			_positionToDescription = {
				{State::Up, {
					PosotionFiel( 0, 2 ), // *  *  o  *  * 
					PosotionFiel( 0, 1 ), // *  *  o  *  *
					PosotionFiel( 0, 0 ), // *  *  0  *  *
					PosotionFiel( 0,-1 )  // *  *  o  *  *
				}},						  // *  *  *  *  *
				{State::Right, {
					PosotionFiel( 2, 0 ), // *  *  *  *  *
					PosotionFiel( 1, 0 ), // *  *  *  *  *
					PosotionFiel( 0, 0 ), // *  o  0  o  o
					PosotionFiel(-1, 0 )  // *  *  *  *  *
				}},						  // *  *  *  *  *
				{State::Down, {
					PosotionFiel( 0, -2), // *  *  *  *  *
					PosotionFiel( 0, -1), // *  *  o  *  *
					PosotionFiel( 0, 0 ), // *  *  0  *  *
					PosotionFiel( 0, 1 )  // *  *  o  *  *
				}},						  // *  *  o  *  *
				{State::Left, {				
					PosotionFiel(-2, 0 ), // *  *  *  *  *
					PosotionFiel(-1, 0 ), // *  *  *  *  *
					PosotionFiel( 0, 0 ), // o  o  0  o  *
					PosotionFiel( 1, 0 )  // *  *  *  *  *
				}}						  // *  *  *  *  *
			};

		};

	};

} // namespace