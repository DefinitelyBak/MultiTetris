#pragma once

#include "Precompile.h"

#include "Commands/AbstractCommand.h"

namespace Tetris::Common
{

    class AbstarctObserver;

    using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

    class AbstractObservable
    {
    public:
        /// @brief 
        virtual ~AbstractObservable() = default;

        /// @brief 
        /// @param  
        void Add(AbstarctObserver* observer);

        /// @brief 
        /// @param  
        void Remove(AbstarctObserver* observer);

        /// @brief 
        void NotifyAll(AbstractCommandPtr command);

    private:
        /// @brief 
        std::unordered_set<AbstarctObserver*> _observers;

        /// @brief
        std::mutex _mutex;  
    };

}