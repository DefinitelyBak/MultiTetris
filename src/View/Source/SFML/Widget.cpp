#include <View/SFML/Widget.h>
#include <Model/AbstractModel.h>


namespace Tetris::View::SFML
{
    Widget::Widget(AbstractModelPtr model, const std::string& pathFont)
        : AbstractWidget(),
          _window(sf::VideoMode({600, 800}), "Tetris"),
          _controller(model),
          _map(sf::Vector2f(420, 800), true),
          _previewBlock(sf::Vector2f(180, 150), true),
          _score(pathFont, sf::Color::White, sf::Text::Bold | sf::Text::Underlined)
    {
        InitializeScore();
        InitializePreviewBlock();
    }

    void Widget::InitializeScore()
    {
        _score.setPosition(sf::Vector2f(460, 400));
        _score.setString("Score:\n0");
        _score.setCharacterSize(30);
    }

    void Widget::InitializePreviewBlock()
    {
        _previewBlock.setPosition(sf::Vector2f(420, 0));
        _previewBlock.SetBlock(AbstractBlockPtr());
    }

    bool Widget::IsOpen() const
    {
        return _windowOpen;
    }

    void Widget::HandleEvents()
    {
        for (sf::Event event;_window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                _windowOpen = false;
            else if (event.type == sf::Event::KeyPressed)
                HandleKeyPress(event.key.scancode);
        }
    }

    void Widget::HandleKeyPress(sf::Keyboard::Scancode scancode)
    {
        switch (scancode)
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

    void Widget::Update()
    {
        if (IsOpen())
        {
            HandleEvents();

            DescriptionModelPtr descriptionModel = GetDescriptionModel();
            if(descriptionModel)
            {
                UpdateMap(descriptionModel);
                UpdatePreviewBlock(descriptionModel);
                UpdateScore(descriptionModel);

                Render();
            }
        }
    }

    void Widget::UpdateMap(const DescriptionModelPtr &descriptionModel)
    {
        _map.SetMap(descriptionModel->map, descriptionModel->size);
    }

    void Widget::UpdatePreviewBlock(const DescriptionModelPtr& descriptionModel)
    {
        if (descriptionModel->nextBlock)
        {
            _previewBlock.SetBlock(descriptionModel->nextBlock);
        }
    }

    void Widget::UpdateScore(const DescriptionModelPtr& descriptionModel)
    {
        if (descriptionModel->score)
        {
            _score.setString("Score:\n" + std::to_string(*descriptionModel->score));
        }
    }

    void Widget::Render()
    {
        _window.clear();
        _window.draw(_map);
        _window.draw(_score);
        _window.draw(_previewBlock);
        _window.display();
    }

    void Widget::SlotCloseWidget()
    {
        _windowOpen = false;
    }
}
