#pragma once

#include "Precompile.h"
#include "Forwards.h"

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
		/// @param columns столбцы
		/// @param rows строки 
		Map(size_t columns = 10, size_t rows = 25);

		/// @brief Получить карту
		/// @return Карта
		DataMap GetMap();

		/// @brief Получиьт размер карты
		/// @return Размер карт
		MapSize GetSize() const;

		/// @brief Блоки заполнелы карту
		/// @return да/нет
		bool IsFullMap() const;

		/// @brief Перезапустить карту
		void Restart();

		/// @brief Установить активную фигуру
		/// @param shape Фигура
		void SetBlock(AbstractBlockPtr shape);

		/// @brief Имеется активная фигура
		/// @return Да/нет
		bool HasActiveBlock();

		/// @brief Переместить фигуру
		/// @param cmn Команда
		void MoveBlock(Command cmn);

		/// @brief Сколько линий было удалено
		unsigned int GetCountDeletedLines();

	private:
		/// @brief Удалить линии
		void DeleteLines();

		/// @brief Возможно ли утсановить блок
		/// @param pos Положение болка
		/// @return да/нет
		bool IsBlockCanMove(Positions pos);

		/// @brief Установить блок на карту
		void SetBlockOnMap(DataMap& map);

		AbstractBlockPtr _activeBlock;
		Position _positionBlock;
		DataMap _data;
		MapSize _size;
		unsigned int _deletedLine{0};
	};

} // namespace