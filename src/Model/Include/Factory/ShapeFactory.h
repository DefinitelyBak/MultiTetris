#pragma once

#include "ObjectFactory.h"

#include "Blocks/Iblock.h"
#include "Blocks/Jblock.h"
#include "Blocks/Lblock.h"
#include "Blocks/Oblock.h"
#include "Blocks/Sblock.h"
#include "Blocks/Tblock.h"
#include "Blocks/Zblock.h"


namespace Tetris::Model::Blocks
{

	/// @brief ID блоков
	enum class IdShape {
		None,
		Iblock,
		Jblock,
		Lblock,
		Oblock,
		Sblock,
		Tblock,
		Zblock
	};

	/// @brief Фабрика блоков
	class ShapeFactory : public ObjectFactory<AbstractBlock, IdShape>
	{
	public:
		/// @brief Создать блок
		/// @param id ID блока
		/// @param color Цвет блока
		/// @return Блок
		AbstractBlock* Create(IdShape id, Common::Data::Color color) 
		{
			return _factory[id]->Create(color);
		}

		/// @brief Получить кол-во блоков
		/// @return Кол-во блоков
		int Size() const 
		{
			return _factory.size();
		};
	};

}