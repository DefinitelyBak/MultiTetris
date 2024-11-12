#pragma once

#include "Commands/AbstractCommand.h"
#include "Data/ThreadsafeQueue.h"


namespace Tetris::Common
{
    class AbstractObservable;

    using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

    /// @brief 
    class AbstarctObserver
    {
    public:
        /// @brief 
        virtual ~AbstarctObserver();

        /// @brief 
        /// @param command 
        void HandleEvent(AbstractCommandPtr command);

        /// @brief 
        /// @param command 
        /// @return 
        bool GetCommand(AbstractCommandPtr& command);

        /// @brief 
        /// @param observable 
        void AddObservable(AbstractObservable* observable);

    protected:
        AbstractObservable* _observable{nullptr};

        /// @brief
        Data::ThreadsafeQueue<AbstractCommandPtr> _queueCommands;
    };

}