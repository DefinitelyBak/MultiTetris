//#include <SFML/Graphics.hpp>

#include "ModelGame.h"
#include "SFMLWidget.h"

#include "boost/signals2.hpp"

void Run()
{

};

// Внутри SFMLWidget соединяется _controller.SignalUpdate с ModelGame::SlotUpdateGame
// Теперь надо связать ModelGame::SignalUpdateView с SFMLWidget::UpdateView

int main()
{
    using namespace Tetris;
    using namespace Tetris::Model;
    using namespace Tetris::View;

    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();
    std::shared_ptr<Tetris::View::SFMLWidget> viewPtr = std::make_shared<Tetris::View::SFMLWidget>(modelPtr);
    
    modelPtr->SignalUpdateView.connect(boost::signals2::signal<void(Tetris::Model::DescriptionMap)>::slot_type
        (&SFMLWidget::SlotUpdateView, viewPtr.get(), boost::placeholders::_1).track_foreign(viewPtr));

    while(viewPtr->IsOpen())
    {
        viewPtr->Update();
    }

}
