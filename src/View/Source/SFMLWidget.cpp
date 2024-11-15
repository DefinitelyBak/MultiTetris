#include "SFMLView.h"


namespace Tetris::View
{

    SFMLWidget::SFMLWidget(/*std::shared_ptr<wigwag::thread_task_executor>& uiThread, */ModelGame& model): _window({1920u, 1080u}, "CMake SFML Project")
    {
        _window.setFramerateLimit(144);

        wigwag::token _token = model.UpdateView.connect([&](DataMap map, MapSize size, unsigned int score){this->SlotUpdate(map, size, score);});
        ///_controller.UpdateModel.connect([&](Command common){model.SlotUpdate(common);});
    }

    void SFMLWidget::Update()
    {

        if (_windowOpen)
        {
            for (auto event = sf::Event(); _window.pollEvent(event);)
            {
               if (event.type == sf::Event::Closed)
               {
                   _window.close();
                   _windowOpen = false;
               }
            }

            // Тут отрисовка окна.

            _window.clear();
            _window.display();
        }

    }

    void SFMLWidget::SlotUpdate(Model::DataMap, Model::MapSize, unsigned int)
    {
        ////
    }

}
