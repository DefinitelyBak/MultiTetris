#pragma once

#include "Precompile.h"

#include "AbstractObserver.h"


namespace Tetris::Common
{

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
        void NotifyAll(const AbstractCommand& command);

    private:
        /// @brief 
        std::unordered_set<AbstarctObserver*> _observers;

        /// @brief
        std::mutex _mutex;  
    };

}