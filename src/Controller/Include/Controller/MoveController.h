#pragma once

#include <Controller/Precompile.h>
#include <Model/Types.h>

#include <Model/AbstractModel.h>


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