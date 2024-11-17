#include "SFMLApplication.h"

#include "Types.h"

Tetris::Application::SFMLApplication::SFMLApplication()
{
     worker = std::make_shared<threadless_task_executor>();
}