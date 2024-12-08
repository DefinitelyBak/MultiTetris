#include "ModelGame.h"
#include "SFML/SFMLApplication.h"
#include "Qt/QtApplication.h"
#include "TimeController.h"


int main(int argc, char *argv[])
{
    
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();

    Tetris::View::SFMLApplication appSfml(modelPtr, 2);
    Tetris::View::QtApplicaion qApp(modelPtr,1);

    Tetris::Controller::TimeController timer(modelPtr, std::chrono::seconds(1));

    while(appSfml.isExecution())
    {
        timer.CheckTimer();
    }
}
