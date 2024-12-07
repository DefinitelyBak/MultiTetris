#pragma once

#include "Precompile.h"
#include "Types.h"

#include "AbstractModel.h"


namespace Tetris::Controller
{

	class MoveController
	{
	public:
		MoveController(AbstractModelPtr model);

		void Move(Model::Command cmn);

	private:
		boost::signals2::signal<void(Model::Command)> SignalUpdateModel;
	};

}