#pragma once

#include "../Precompile.h"

#include "Data/Color.h"


namespace Tetris::Model::Blocks
{

	/// @brief Базовый класс фигур 
	class AbstractBlock
	{
	public:
		/// @brief Состояние фигуры
		enum class State: int
		{
			Up = 1,
			Right,
			Down,
			Left
		};
		
		/// @brief Координаты поля фигры относительно центра фигуры, координаты x, y
		using PosotionFiel = std::pair<int, int>;

		/// @brief Контейнер - описание положение фигуры
		using DescriptionFigure = std::array<PosotionFiel, 4>;

		/// @brief Тип положение - описание фигуры
		using PositionToDescription = std::unordered_map<State, DescriptionFigure>;

		/// @brief Дефолдный конструктор
		AbstractBlock(Common::Data::Color color);

		/// @brief Виртуальный деструктор
		virtual ~AbstractBlock() = default;

		/// @brief Получить положение фигуры
		/// @return Описание фигуры
		DescriptionFigure GetDescription();

		/// @brief Получит состояние фигуры
		/// @return состояние фигуры
		State GetState() const;

		/// @brief Вернуть цыет фигуры
		/// @return Цвет фигуры 
		Common::Data::Color GetColor() const;

		/// @brief Повернуть фигуру
		void RotateShape();

		/// @brief Получить полжение фигуры при возможном повороте
		/// @return Возможное положение фигуры
		DescriptionFigure TryRotateShape();

	private:
		/// @brief Изменить состояние фигуры
		/// @param state Изменяемое состояние
		void ChangeState(State& state);

	protected:
		/// @brief Контейнер состояние - положение
		PositionToDescription _positionToDescription;

	private:
		/// @brief Состояние фигуры
		State _state {State::Up};

		/// @brief Цвет фигуры
		Common::Data::Color _color; 
	};

}

