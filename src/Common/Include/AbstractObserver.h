#pragma once

#include "Commands/AbstractCommand.h"
#include "Data/ThreadsafeQueue.h"


namespace Tetris::Common
{
    /// @brief 
    class AbstarctObserver
    {
    public:
        /// @brief 
        virtual ~AbstarctObserver() = default;

        /// @brief 
        /// @param command 
        void HandleEvent(const AbstractCommand& command);

        /// @brief 
        /// @param command 
        /// @return 
        bool GetCommand(AbstractCommand& command);

    protected:
        /// @brief 
        Data::ThreadsafeQueue<AbstractCommand> _queueCommands;
    };

}