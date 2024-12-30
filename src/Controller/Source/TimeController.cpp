#include <Controller/TimeController.h>


namespace Tetris::Controller
{
		TimeController::TimeController(AbstractModelPtr model, std::chrono::seconds interval): _interval(interval)
        {
            SignalUpdateModel.connect(boost::signals2::signal<void(Model::Command)>::slot_type
                (&Model::AbstractModel::SlotUpdate, model.get(), boost::placeholders::_1).track_foreign(model));

             _start = std::chrono::system_clock::now();
        }

		void TimeController::CheckTimer()
        {
            if(std::chrono::system_clock::now() - _start > _interval)
            {
                SignalUpdateModel(Model::Command::Down);
                _start = std::chrono::system_clock::now();
            }
        }
}