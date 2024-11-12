#include "AbstractObserver.h"

#include "AbstractObservable.h"

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

    void AbstarctObserver::AddObservable(AbstractObservable *observable)
    {
        _observable = observable;
    }

    AbstarctObserver::~AbstarctObserver()
    {
        if(_observable)
            _observable->Remove(this);
    }

    void AbstarctObserver::HandleEvent(AbstractCommandPtr command)
    {
        _queueCommands.push(command);
    }

}
