#include "AbstractObservable.h"


namespace Tetris::Common
{

    void AbstractObservable::Add(AbstarctObserver* observer)
    {
        if (!observer)
            return;

        const std::lock_guard<std::mutex> lock(_mutex);
        _observers.insert(observer);
    }

    void AbstractObservable::Remove(AbstarctObserver* observer)
    {
        if (!observer)
            return;

        const std::lock_guard<std::mutex> lock(_mutex);

        if (_observers.contains(observer))
            _observers.erase(observer);
    }

    void AbstractObservable::NotifyAll(const AbstractCommand& command)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        for(auto& observer: _observers)
            observer->HandleEvent(command);
    }

}