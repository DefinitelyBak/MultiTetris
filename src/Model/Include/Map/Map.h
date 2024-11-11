#pragma once

#include "Precompile.h"

#include "Blocks/AbstractBlock.h"


/// 1 линия — 100 очков, 2 линии — 300 очков, 3 линии — 700 очков, 4 линии (то есть сделать Тетрис) — 1500 очков
namespace Tetris::Model::Map
{

	using namespace Model;
	using namespace Common;
	using namespace Blocks;

	// Начало системы координат в левом нижнем углу.
	/// @brief Класс реализации карты
	class Map
	{
	public:
		/// @brief Конструктор по умолчанию, инициализирует пустую карту
		/// @param x 
		/// @param y 
		Map(size_t columns = 10, size_t rows = 40);

		Map(const std::vector<Data::Color>& map, size_t columns, size_t rows);

		/// @brief Получить карту
		/// @return Карта
		std::vector<Data::Color> GetMap() const;

		/// @brief 
		/// @return 
		std::pair<size_t, size_t> GetSize();

		size_t GetLastNotFreeLine() const;

		/// @brief Установить активную фигуру
		/// @param shape Фигура
		void SetNewBlock(const std::shared_ptr<AbstractBlock> shape);

		/// @brief Имеется активная фигура
		/// @return Да/нет
		bool HasActiveBlock() const;

		/// @brief Переместить фигуру
		/// @param cmn Команда
		void MoveBlock(Command cmn);

		/// @brief Сколько линий было удалено
		int CountDeletedLines();

	private:
		/// @brief 
		/// @param numberLine 
		/// @return 
		bool CheckLine(std::size_t numberLine) const;

		int DeleteLines();

		/// @brief 
		/// @param cmn 
		/// @return 
		bool CheckMoveBlock(Positions cmn);

		/// @brief 
		void SetBlockOnMap();

		/// @brief 
		std::shared_ptr<AbstractBlock> _activeBlock;

		/// @brief 
		Position _positionBlock;
	
		std::vector<Data::Color> _data;

		/// @brief 
		int _deletedLine{0};

		size_t _columns;

		size_t _rows;

	};

} // namespace