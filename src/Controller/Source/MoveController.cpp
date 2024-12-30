#include <Controller/MoveController.h>


namespace Tetris::Controller
{
    MoveController::MoveController(AbstractModelPtr model)
    {
		SignalUpdateModel.connect(boost::signals2::signal<void(Model::Command)>::slot_type
        	(&Model::AbstractModel::SlotUpdate, model.get(), boost::placeholders::_1).track_foreign(model));
    }

    void MoveController::Move(Model::Command cmn)
	{
		SignalUpdateModel(cmn);
	}

}