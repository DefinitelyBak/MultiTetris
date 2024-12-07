#include "ModelGame.h"
#include "SFMLApplication.h"
#include "TimeController.h"


int main()
{
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();

    Tetris::View::SFMLApplication appSfml(modelPtr, 2);
    
    Tetris::Controller::TimeController timer(modelPtr, std::chrono::seconds(1));

    while(appSfml.isExecution())
    {
        timer.CheckTimer();
    }
}
