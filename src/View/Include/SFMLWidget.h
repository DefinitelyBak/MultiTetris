#pragma once

#include "AbstractWidget.h"

#include <SFML/Graphics.hpp>


#include "ModelGame.h"
#include "MoveController.h"
#include "SFMLMap.h"
#include "SFMLPreviewBlock.h"

#include "Types.h"


namespace Tetris::View
{
    using namespace Model;
    using ModelGamePtr = std::shared_ptr<ModelGame>;

    class SFMLWidget : public AbstractWidget
    {
    public:
    
        SFMLWidget(ModelGamePtr& model);

        ~SFMLWidget() override = default;

        void Update() override;

        void SlotUpdateView(DescriptionMap) override;

        bool IsOpen() const override;

    private:
        sf::RenderWindow _window;

        Controller::MoveController _controller;

        bool _windowOpen{true};
        SFMLMap _map;
        SFMLPreviewBlock _previwBlock;
        sf::Text _score;
        sf::Font _font;
    };
}
