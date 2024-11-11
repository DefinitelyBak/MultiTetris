#pragma once

#include "Precompile.h"

#include "AbstractObservable.h"


/// @brief 
namespace Tetris::Controller
{

	enum class Command: int
	{
		Right,
		Left,
		Down,
		RotateRight,
		RotateLeft
	};

	using namespace Common;

	/// @brief 
	class MoveController: public AbstractObservable
	{
	public:
		/// @brief 
		MoveController();

		/// @brief 
		void Move(Command cmn);
	};

}