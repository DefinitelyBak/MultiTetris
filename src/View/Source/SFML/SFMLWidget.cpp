#include "SFML/SFMLWidget.h"

#include "AbstractModel.h"


namespace Tetris::View
{
    SFMLWidget::SFMLWidget(AbstractModelPtr model, std::string pathFont): AbstractWidget(),
            _window({600u,800u}, "Tetris"),
            _controller(model),
            _map(sf::Vector2f(420,800), true),
            _previwBlock(sf::Vector2f(180, 150), true),
            _score(pathFont, sf::Color::White, sf::Text::Bold | sf::Text::Underlined)
    {
        _score.setPosition(sf::Vector2f(460, 400));
        _score.setString("Score:\n0");
        _score.setCharacterSize(30);

        _previwBlock.setPosition(sf::Vector2f(420, 0));
        _previwBlock.SetBlock(Model::IdShape::None, Model::TypeColor::None);
    }

    bool SFMLWidget::IsOpen() const
    {
        return _windowOpen;
    }

    void SFMLWidget::UpdateWidget()
    {
        if (IsOpen())
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
                        _controller.Move(Model::Command::Left);
                        break;
                    case sf::Keyboard::Scan::Right:
                        _controller.Move(Model::Command::Right);
                        break;
                    case sf::Keyboard::Scan::Up:
                        _controller.Move(Model::Command::RotateRight);
                        break;
                    case sf::Keyboard::Scan::Down:
                        _controller.Move(Model::Command::Down);
                        break;
                    default:
                        break;
                    }
                }
            }

            Model::DescriptionModel descriptionModel = GetDescriptionModel();
            _map.SetMap(descriptionModel.map, descriptionModel.size.rows, descriptionModel.size.columns);
            if (descriptionModel.nextBlock)
                _previwBlock.SetBlock(descriptionModel.nextBlock->typeBlock, descriptionModel.nextBlock->color);
            if (descriptionModel.score)
                _score.setString("Score:\n" + std::to_string(*descriptionModel.score));

            _window.clear();
            _window.draw(_map);
            _window.draw(_score);
            _window.draw(_previwBlock);
            _window.display();
        }
    }

    void SFMLWidget::SlotCLoseEvent()
    {
        _windowOpen = false;
    }
}
