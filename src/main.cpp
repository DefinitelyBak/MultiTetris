//#include <SFML/Graphics.hpp>

#include "ModelGame.h"
#include "SFMLWidget.h"

#include "boost/signals2.hpp"

void Run()
{

};

int main()
{
    using namespace Tetris;
    using namespace Tetris::Model;
    using namespace Tetris::View;

    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();
    std::shared_ptr<Tetris::View::SFMLWidget> viewPtr = std::make_shared<Tetris::View::SFMLWidget>(modelPtr);
    std::shared_ptr<Tetris::View::SFMLWidget> viewPtr1 = std::make_shared<Tetris::View::SFMLWidget>(modelPtr);
    
    modelPtr->SetView(viewPtr);
    modelPtr->SetView(viewPtr1);

    while(viewPtr->IsOpen())
    {
        viewPtr->Update();
        viewPtr1->Update();
    }

}
