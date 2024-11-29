#pragma once

#include "Precompile.h"

#include "Types.h"
#include <boost/signals2.hpp>


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
		boost::signals2::signal<void(Model::Command)> SignalUpdateModel; 
	};

}