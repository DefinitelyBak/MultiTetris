#include "AbstractObserver.h"


namespace Tetris::Common
{

    bool AbstarctObserver::GetCommand(AbstractCommand& command)
    {
        if (_queueCommands.empty())
            return false;

        AbstractCommand newCommand;

        if(!_queueCommands.try_pop(newCommand))
            return false;

        command = newCommand;
        return true;
    }

    void AbstarctObserver::HandleEvent(const AbstractCommand& command)
    {
        _queueCommands.push(command);
    }

}
