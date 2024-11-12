#pragma once

#include "Precompile.h"

#include "AbstractObservable.h"
#include "Data/Types.h"

/// @brief 
namespace Tetris::Controller
{
	using namespace Common;

	/// @brief 
	class MoveController: public AbstractObservable
	{
	public:
		/// @brief 
		MoveController();

		/// @brief 
		void Move(Data::Command cmn);
	};

}