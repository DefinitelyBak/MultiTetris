#include "SFMLWidget.h"

#include <boost/signals2.hpp>
#include <utility>

#include <iostream>

#define X TypeColor::None
#define Y TypeColor::Green
#define Z TypeColor::Red


namespace Tetris::View
{
    SFMLWidget::SFMLWidget(ModelGamePtr& model): AbstractWidget(),  _window({420u,800u}, "Tetris"), _map(sf::Vector2f(420,800))
    {
        _controller.SignalUpdateModel.connect(boost::signals2::signal<void(Model::Command)>::slot_type
            (&ModelGame::SlotUpdate, model.get(), boost::placeholders::_1).track_foreign(model));
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
                   break;
               }

                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.scancode)
                    {
                    case sf::Keyboard::Scan::Left:
                        _controller.Move(Command::Left);
                        break;
                    case sf::Keyboard::Scan::Right:
                        _controller.Move(Command::Right);
                        break;
                    case sf::Keyboard::Scan::Up:
                        _controller.Move(Command::RotateRight);
                        break;
                    case sf::Keyboard::Scan::Down:
                        _controller.Move(Command::Down);
                        break;
                    default:
                        break;
                    }
                }
            }

            _window.clear();
            _window.draw(_map);
            _window.display();
        }

    }

    void SFMLWidget::SlotUpdateView(DescriptionMap map)
    {
        _map.SetMap(map.map, map.size.rows, map.size.columns);
    }

    bool SFMLWidget::IsOpen() const
    {
        return _windowOpen;
    }

}
