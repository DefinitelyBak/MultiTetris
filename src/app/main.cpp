//#include <SFML/Graphics.hpp>

#include "ModelGame.h"
#include "SFMLWidget.h"

#include "boost/signals2.hpp"

void Run()
{

};

// Внутри SFMLWidget соединяется _controller.SignalUpdate с ModelGame::SlotUpdateGame
// Теперь надо связать ModelGame::SignalUpdateView с SFMLWidget::UpdateView // Можно сделать в Model метод SetView(std::shared_ptr<SFMLWidget>)

int main()
{
    using namespace Tetris;
    using namespace Tetris::Model;
    using namespace Tetris::View;

    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();
    std::shared_ptr<Tetris::View::SFMLWidget> viewPtr = std::make_shared<Tetris::View::SFMLWidget>(modelPtr);
    
    modelPtr->SetView(viewPtr);

    while(viewPtr->IsOpen())
    {
        viewPtr->Update();
    }

}
