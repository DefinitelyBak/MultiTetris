#include "AbstractObserver.h"


namespace Tetris::Common
{

    bool AbstarctObserver::GetCommand(AbstractCommandPtr& command)
    {
        if (_queueCommands.empty())
            return false;

        AbstractCommandPtr newCommand;

        if(!_queueCommands.try_pop(newCommand))
            return false;

        command = newCommand;
        return true;
    }

    void AbstarctObserver::HandleEvent(AbstractCommandPtr command)
    {
        _queueCommands.push(command);
    }

}
