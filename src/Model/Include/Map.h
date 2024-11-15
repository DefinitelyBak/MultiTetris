#pragma once

#include "Precompile.h"

#include "Types.h"
#include "blocks/AbstractBlock.h"


namespace Tetris::Model
{
	using namespace Blocks;

	// Начало системы координат в левом нижнем углу.
	/// @brief Класс реализации карты
	class Map
	{
	public:
		/// @brief Конструктор по умолчанию, инициализирует пустую карту
		/// @param x 
		/// @param y 
		Map(size_t columns = 10, size_t rows = 25);

		/// @brief Получить карту
		/// @return Карта
		DataMap GetMap() const;

		/// @brief 
		/// @return 
		MapSize GetSize();

		//size_t GetLastNotFreeLine() const;

		/// @brief Установить активную фигуру
		/// @param shape Фигура
		void SetBlock(std::unique_ptr<AbstractBlock> shape);

		/// @brief Имеется активная фигура
		/// @return Да/нет
		bool HasActiveBlock();

		/// @brief Переместить фигуру
		/// @param cmn Команда
		void MoveBlock(Command cmn);

		/// @brief Сколько линий было удалено
		unsigned int GetCountDeletedLines();

	private:
		/// @brief 
		/// @return 
		void DeleteLines();

		/// @brief 
		/// @param cmn 
		/// @return 
		bool IsBlockCanMove(Positions cmn);

		/// @brief 
		void SetBlockOnMap();

		/// @brief 
		std::unique_ptr<AbstractBlock> _activeBlock;

		/// @brief 
		Position _positionBlock;
	
		DataMap _data;

		MapSize _size;

		/// @brief 
		unsigned int _deletedLine{0};
	};

} // namespace