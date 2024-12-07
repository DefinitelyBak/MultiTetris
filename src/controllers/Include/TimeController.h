#pragma once

#include "Precompile.h"
#include "Types.h"

#include "AbstractModel.h"


namespace Tetris::Controller
{

	class TimeController
	{
	public:
		TimeController(AbstractModelPtr model, std::chrono::seconds interval);

		void CheckTimer();

    private:
		boost::signals2::signal<void(Model::Command)> SignalUpdateModel;

        std::chrono::seconds _interval;

        std::chrono::time_point<std::chrono::system_clock> _start;
	};

}