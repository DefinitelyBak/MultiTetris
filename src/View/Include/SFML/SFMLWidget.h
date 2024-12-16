#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include "AbstractModel.h"
#include "ModelGame.h"
#include "MoveController.h"
#include "SFMLMap.h"
#include "SFMLText.h"
#include "SFMLPreviewBlock.h"


namespace Tetris::View
{

    class SFMLWidget final : public Model::IWidget 
    {
    public:
        SFMLWidget(AbstractModelPtr model, std::string pathFont);

        ~SFMLWidget() override = default;

        void Update() override;

        bool IsOpen() const override;

        void SlotCLoseWidget() override;

    private:
        sf::RenderWindow _window;

        Controller::MoveController _controller;

        std::atomic<bool> _windowOpen{true};
        SFMLMap _map;
        SFMLPreviewBlock _previwBlock;
        SFMLText _score;

        std::stack<sf::Event> _uievents;
    };
}
