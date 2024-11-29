#include "MoveController.h"


namespace Tetris::Controller
{
	
	void MoveController::Move(Model::Command cmn)
	{
		SignalUpdateModel(cmn);
	}

}