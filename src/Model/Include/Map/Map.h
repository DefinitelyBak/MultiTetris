#pragma once

#include "../Precompile.h"

#include "Blocks/AbstractBlock.h";
#include "Data/Field.h"


/// 1 линия — 100 очков, 2 линии — 300 очков, 3 линии — 700 очков, 4 линии (то есть сделать Тетрис) — 1500 очков
namespace Tetris::Model::Map
{

	using namespace Common;
	using namespace Blocks;

	enum class Command: int
	{
		Up = 1,
		Right,
		Down,
		Left
	};

	// Начало системы координат в левом нижнем углу.
	/// @brief Класс реализации карты
	class Map
	{
	public:
		/// @brief Тип положение блока на карте
		using PositionBlock = std::pair<int, int>;

		/// @brief Тип 
		using MapType = std::vector<std::vector<Data::Field>>;

		/// @brief Конструктор по умолчанию, инициализирует пустую карту
		/// @param x 
		/// @param y 
		Map(size_t x = 10, size_t y = 20);

		/// @brief Установить активную фигуру
		/// @param shape Фигура
		void SetBlock(const std::shared_ptr<AbstractBlock> shape);

		/// @brief Установить карту
		/// @param map Новая карта
		void SetMap(const MapType& map);

		/// @brief Имеется активная фигура
		/// @return Да/нет
		bool HasActiveBlock() const;

		/// @brief Переместить фигуру
		/// @param cmn Команда
		void MoveBlock(Command cmn);

		/// @brief Сколько линий было удалено
		void CountDeletedLines();

		/// @brief Получить карту
		/// @return Карта
		const MapType& GetMap() const;

		/// @brief 
		/// @return 
		std::pair<size_t, size_t> GetSize();

	private:
		/// @brief 
		/// @param numberLine 
		/// @return 
		bool CheckLine(int numberLine);

		/// @brief 
		/// @param cmn 
		/// @return 
		bool CheckMoveBlock(Command cmn);

		/// @brief 
		std::shared_ptr<AbstractBlock> _activeBlock;

		/// @brief 
		PositionBlock _positionBlock;
	
		MapType _data;

		/// @brief 
		int _deletedLine{0};

	};

} // namespace