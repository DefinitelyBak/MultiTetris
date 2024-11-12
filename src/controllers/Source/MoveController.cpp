#include "MoveController.h"

#include "Commands/AbstractCommand.h"
#include "Commands/MoveCommand.h"

namespace Tetris::Controller
{

	using namespace Common;
	using namespace Common::Data;

		/// @brief 
		MoveController::MoveController(): AbstractObservable()
		{}

		/// @brief 
		void MoveController::Move(Data::Command cmn)
		{
			AbstractCommandPtr command;

			switch (cmn)
			{
			case Command::Right:
				command = std::make_shared<MoveCommand>(Data::Command::Right);
				break;
			case Command::Left:
				command = std::make_shared<MoveCommand>(Data::Command::Left);
				break;
			case Command::Down:
				command = std::make_shared<MoveCommand>(Data::Command::Down);
				break;
			case Command::RotateRight:
				command = std::make_shared<MoveCommand>(Data::Command::RotateRight);
				break;
			case Command::RotateLeft:
				command = std::make_shared<MoveCommand>(Data::Command::RotateLeft);
				break;
			default:
				break;
			}

			if(command)
				NotifyAll(command);

		}

}