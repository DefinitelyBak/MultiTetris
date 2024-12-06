#pragma once

#include "Precompile.h"
#include "AbstractWidget.h"
#include "AbstractModel.h"

#include <SFML/Graphics.hpp>


#include "ModelGame.h"
#include "MoveController.h"
#include "SFMLMap.h"
#include "SFMLText.h"
#include "SFMLPreviewBlock.h"

#include "Types.h"


namespace Tetris::View
{
    using namespace Model;
    using ModelGamePtr = std::shared_ptr<ModelGame>;

    class SFMLWidget final : public AbstractWidget 
    {
    public:
    
        SFMLWidget(std::shared_ptr<AbstractModel> model, std::string pathFont);

        ~SFMLWidget() override = default;

        bool IsOpen() const override;

    protected:

        void UpdateWidget() override;

        void ProcessingEvents() override;

        void UpdateView(Model::DescriptionModel descriptionModel) override;

    private:
        sf::RenderWindow _window;

        Controller::MoveController _controller;

        bool _windowOpen{true};
        SFMLMap _map;
        SFMLPreviewBlock _previwBlock;
        SFMLText _score;

        std::stack<sf::Event> _uievents;
    };
}
