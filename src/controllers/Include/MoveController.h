#pragma once

#include "Precompile.h"

#include "Types.h"
#include <wigwag/signal.hpp>


/// @brief 
namespace Tetris::Controller
{
	/// @brief 
	class MoveController
	{
	public:
		/// @brief 
		MoveController() = default;

		/// @brief 
		void Move(Model::Command cmn);

		/// @brief 
		wigwag::signal<void(Model::Command)> UpdateModel;
	};

}