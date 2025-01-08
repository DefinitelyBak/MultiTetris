#include <Controller/TimeController.h>


namespace Tetris::Controller
{
    TimeController::TimeController(AbstractModelPtr model, std::chrono::duration<double> interval):
        _interval(interval), _moveController(model), _start(std::chrono::system_clock::now())
    {}

    void TimeController::CheckTimer()
    {
        auto now = std::chrono::system_clock::now();
        if (now - _start < _interval)
            return;

        _moveController.Move(Model::Command::Down);
        _start = now;
    }
}