#pragma once

#include "Commands/AbstractCommand.h"
#include "Data/ThreadsafeQueue.h"


namespace Tetris::Common
{
    using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

    /// @brief 
    class AbstarctObserver
    {
    public:
        /// @brief 
        virtual ~AbstarctObserver() = default;

        /// @brief 
        /// @param command 
        void HandleEvent(AbstractCommandPtr command);

        /// @brief 
        /// @param command 
        /// @return 
        bool GetCommand(AbstractCommandPtr& command);

    protected:
        /// @brief 
        Data::ThreadsafeQueue<AbstractCommandPtr> _queueCommands;
    };

}