#pragma once

#include <chrono>
#include <iostream>
#include <thread>

//#include <wigwag/threadless_task_executor.hpp>
#include <wigwag/task_executor.hpp>
#include <wigwag/thread_task_executor.hpp>
#include <memory>

#include <wigwag/life_token.hpp>
#include <wigwag/listenable.hpp>
#include <wigwag/signal.hpp>
#include <wigwag/thread_task_executor.hpp>
#include <wigwag/threadless_task_executor.hpp>
#include <wigwag/token_pool.hpp>


namespace Tetris::Application
{
using namespace wigwag;

    class SFMLApplication
    {
    public:

        SFMLApplication();

        void Run();

        void AddWidgte();

    private:

        std::shared_ptr<threadless_task_executor> worker;

    };

}