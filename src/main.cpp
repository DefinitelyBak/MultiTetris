#include "ModelGame.h"
#include "SFML/SFMLApplication.h"
#include "Qt/QtApplication.h"
#include "TimeController.h"


int main(int argc, char *argv[])
{   
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();

    std::vector<Tetris::View::AbstractApplicationPtr> applications;
    applications.push_back(std::make_shared<Tetris::View::SFML::SFMLApplication>(modelPtr, 1, "C:/Projects/MultiTetris/src/View/Resources/arial_bolditalicmt.ttf"));
    applications.push_back(std::make_shared<Tetris::View::Qt::QtApplicaion>(modelPtr, 1));

    Tetris::Controller::TimeController timer(modelPtr, std::chrono::seconds(1));

    while(!applications.empty())
    {
        std::erase_if(applications, [](Tetris::View::AbstractApplicationPtr app){return !app->isExecution();});
        timer.CheckTimer();
    }
}
