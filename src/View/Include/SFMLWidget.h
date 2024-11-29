#pragma once

#include "AbstractWidget.h"

#include <SFML/Graphics.hpp>


#include "ModelGame.h"
#include "MoveController.h"
#include "SFMLMap.h"

#include "Types.h"


namespace Tetris::View
{
    using namespace Model;
    using ModelGamePtr = std::shared_ptr<ModelGame>;

    class SFMLWidget : public AbstractWidget
    {
    public:
    
        SFMLWidget(ModelGamePtr& model);

        void Update() override;

        void SlotUpdateView(DescriptionMap);

        bool IsOpen() const override;

    private:
        sf::RenderWindow _window;

        Controller::MoveController _controller;

        bool _windowOpen{true};
        SFMLMap _map;
    };
}
