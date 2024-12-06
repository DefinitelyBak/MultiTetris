#include "SFMLWidget.h"

#include <boost/signals2.hpp>
#include <utility>
#include <stdexcept>


namespace Tetris::View
{
    SFMLWidget::SFMLWidget(std::shared_ptr<AbstractModel> model, std::string pathFont): AbstractWidget(),  _window({600u,800u}, "Tetris"),
        _map(sf::Vector2f(420,800), true), _previwBlock(sf::Vector2f(180, 150), true),
        _score(pathFont, sf::Color::White, sf::Text::Bold | sf::Text::Underlined)
    {
        _controller.SignalUpdateModel.connect(boost::signals2::signal<void(Model::Command)>::slot_type
            (&AbstractModel::SlotUpdate, model.get(), boost::placeholders::_1).track_foreign(model));

        /// Шрифт
        _score.setPosition(sf::Vector2f(460, 400));
        _score.setString("Score:\n0");
        _score.setCharacterSize(30);

        /// Превью фигуры.
        _previwBlock.setPosition(sf::Vector2f(420, 0));
        _previwBlock.SetBlock(Model::IdShape::None, Model::TypeColor::None);
    }

    void SFMLWidget::UpdateWidget()
    {
        if (_windowOpen)
        {
            for (auto event = sf::Event(); _window.pollEvent(event);)
            {
               if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
               {
                    _uievents.push(event);
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

    void SFMLWidget::UpdateView(Model::DescriptionModel descriptionModel)
    {
        _map.SetMap(descriptionModel.map, descriptionModel.size.rows, descriptionModel.size.columns);
        if (descriptionModel.nextBlock)
            _previwBlock.SetBlock(descriptionModel.nextBlock->nextBlock, descriptionModel.nextBlock->color);
        if (descriptionModel.score)
            _score.setString("Score:\n" + std::to_string(*descriptionModel.score));
    }

    bool SFMLWidget::IsOpen() const
    {
        return _windowOpen;
    }

}
