#pragma once

#include "ObjectFactory.h"
#include "blocks/Iblock.h"
#include "blocks/Jblock.h"
#include "blocks/Lblock.h"
#include "blocks/Oblock.h"
#include "blocks/Sblock.h"
#include "blocks/Tblock.h"
#include "blocks/Zblock.h"


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
		AbstractBlock* Create(IdShape id, TypeColor color) 
		{
			return _factory[id]->Create(color);
		}

		/// @brief Получить кол-во инициализированных блоков
		/// @return Колличество
		int Size() const 
		{
			return _factory.size();
		};
	};

}