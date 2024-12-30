#include <Model/ModelGame.h>

#include <View/SFML/SFMLApplication.h>
#include <View/Qt/QtApplication.h>
#include <Controller/TimeController.h>

int main(int argc, char *argv[])
{   
    
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();

    Tetris::View::SFML::SFMLApplication sfmlApp(modelPtr, 1, "C:/Projects/MultiTetris/src/View/Resources/arial_bolditalicmt.ttf");
    Tetris::View::Qt::QtApplicaion qtApp(modelPtr, 1);

    Tetris::Controller::TimeController timer(modelPtr, std::chrono::seconds(1));

    while(sfmlApp.isExecution() || qtApp.isExecution())
    {
        timer.CheckTimer();
    }
}
