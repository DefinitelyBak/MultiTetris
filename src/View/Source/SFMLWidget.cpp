#include "SFMLWidget.h"

#include <boost/signals2.hpp>
#include <utility>
#include <stdexcept>


namespace Tetris::View
{
    SFMLWidget::SFMLWidget(ModelGamePtr& model): AbstractWidget(),  _window({600u,800u}, "Tetris"), _map(sf::Vector2f(420,800), true), _previwBlock(sf::Vector2f(180, 150), true)
    {
        _controller.SignalUpdateModel.connect(boost::signals2::signal<void(Model::Command)>::slot_type
            (&ModelGame::SlotUpdate, model.get(), boost::placeholders::_1).track_foreign(model));

        /// Шрифт
        if (!_font.loadFromFile("C:\\Projects\\ProjectTetris\\Tetris\\src\\view\\Resources\\tuffy.ttf"))
        {
            throw(std::invalid_argument("Invalid path to font"));
        }
        _score.setFont(_font);
        _score.setString("Score:\n0");
        _score.setFillColor(sf::Color::White);
        _score.setCharacterSize(30);
        _score.setStyle(sf::Text::Bold | sf::Text::Underlined);
        _score.setPosition(sf::Vector2f(460, 400));

        /// Превью фигуры.
        _previwBlock.SetBlock(Model::IdShape::None, Model::TypeColor::None);
        _previwBlock.setPosition(sf::Vector2f(420, 0));
    }

    void SFMLWidget::UpdateWidget()
    {
        if (_windowOpen)
        {
            for (auto event = sf::Event(); _window.pollEvent(event);)
            {
               if (event.type == sf::Event::Closed)
               {
                    _uievents.push(event);
                   //_window.close();
                   //_windowOpen = false;
                   //break;
               }

                if (event.type == sf::Event::KeyPressed)
                {
                    _uievents.push(event);
                    /*
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
                    */
                }
            }

            _window.clear();
            _window.draw(_map);
            _window.draw(_score);
            _window.draw(_previwBlock);
            _window.display();
        }
    }

    void SFMLWidget::ProcessingEvents()
    {
        while(!_uievents.empty())
        {
            sf::Event event = _uievents.top();
            _uievents.pop();
            
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
    }

    void SFMLWidget::UpdateView(DescriptionMap map)
    {
        _map.SetMap(map.map, map.size.rows, map.size.columns);
    }

    void SFMLWidget::SetNextBlock(Model::DescriptionBlock nextBlock)
    {
        _previwBlock.SetBlock(nextBlock.nextBlock, nextBlock.color);
    }

    void SFMLWidget::SetScore(unsigned int score)
    {
        _score.setString("Score:\n" + std::to_string(score));
    }

    bool SFMLWidget::IsOpen() const
    {
        return _windowOpen;
    }

}
