#pragma once

#include "../Precompile.h"

#include "Types.h"
#include "Data/Color.h"


namespace Tetris::Model::Blocks
{

	/// @brief Базовый класс блока 
	class AbstractBlock
	{
	public:
		/// @brief Тип состояния - описание блока
		using StateToPositions = std::unordered_map<State, Positions>;

		/// @brief Тип состояние - смещения
		using StateToOffsets = std::unordered_map<State, Offsets>;

		/// @brief Дефолдный конструктор
		AbstractBlock(Common::Data::Color color);

		/// @brief Виртуальный деструктор
		virtual ~AbstractBlock() = default;

		/// @brief Вернуть цвет блока
		/// @return Цвет блока 
		Common::Data::Color GetColor() const;

		/// @brief Получить текущее положение блока
		/// @return Описание блока
		Positions GeCurrentDescription();

		/// @brief Получить положение блока по состоянию блока
		/// @return Состояние блока
		Positions GetDescription(State state);

		/// @brief Получит состояние блока
		/// @return состояние блока
		State GeCurrentState() const;

		/// @brief Получить следующее состояние блока по переданной команде
		/// @param cmd Команда
		/// @return Состояние
		State GetNextState(Command cmd) const;

		/// @brief Получить смещение для блока
		/// @param from Начальное состояние 
		/// @param to К которому необходимо прийти
		/// @return Смещения
		Offsets GetOffsets(State from, State to);

		/// @brief Повернуть блок
		void RotateBlock(Command cmd);

	protected:
		/// @brief Контейнер состояние - положение
		StateToPositions _stateToPositions;

		/// @brief Контейнер состояние - смещение
		StateToOffsets _stateToOffset;

	private:
		/// @brief Состояние блока
		State _state {State::Up};

		/// @brief Цвет блока
		Common::Data::Color _color; 
	};

	const AbstractBlock::StateToOffsets JLSTZOffset
	{
		{State::Up,
			{
				Position( 0, 0), 
				Position( 0, 0), 
				Position( 0, 0), 
				Position( 0, 0),
				Position( 0, 0) 
			}				    
		},
		{State::Right,
			{
				Position( 0, 0), 
				Position( 1, 0), 
				Position( 1,-1), 
				Position( 0, 2),
				Position( 1, 2),
			}				    
		},					   
		{State::Down,
			{
				Position( 0, 0),  
				Position( 0, 0),  
				Position( 0, 0),  
				Position( 0, 0),
				Position( 0, 0)   
			}				     
		},					     
		{State::Left,
			{
				Position( 0, 0), 
				Position(-1, 0), 
				Position(-1,-1), 
				Position( 0, 2),
				Position(-1, 2),
			}
		} 
	};

	const AbstractBlock::StateToOffsets IOffset
	{
		{State::Up,
			{
				Position( 0, 0), 
				Position(-1, 0), 
				Position( 2, 0), 
				Position(-1, 0),
				Position( 2, 0) 
			}				    
		},
		{State::Right,
			{
				Position(-1, 0), 
				Position( 0, 0), 
				Position( 0, 0), 
				Position( 0, 1),
				Position( 0,-2),
			}				    
		},					   
		{State::Down,
			{
				Position(-1, 1),  
				Position( 1, 1),  
				Position(-2, 1),  
				Position( 1, 0),
				Position(-2, 0)   
			}				     
		},					     
		{State::Left,
			{
				Position(0, 1), 
				Position(0, 1), 
				Position(0, 1), 
				Position(0,-1),
				Position(0, 2),
			}
		} 
	};

const AbstractBlock::StateToOffsets OOffset
	{
		{State::Up,
			{
				Position( 0, 0), 
				Position( 0, 0), 
				Position( 0, 0), 
				Position( 0, 0), 
				Position( 0, 0)
			}				    
		},
		{State::Right,
			{
				Position( 0,-1), 
				Position( 0,-1), 
				Position( 0,-1), 
				Position( 0,-1), 
				Position( 0,-1)
			}				    
		},					   
		{State::Down,
			{
				Position(-1,-1),  
				Position(-1,-1),  
				Position(-1,-1),  
				Position(-1,-1),  
				Position(-1,-1)
			}				     
		},					     
		{State::Left,
			{
				Position(-1, 0), 
				Position(-1, 0), 
				Position(-1, 0), 
				Position(-1, 0), 
				Position(-1, 0)
			}
		} 
	};

}

