#pragma once

#include "Precompile.h"
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

    class SFMLWidget final : public AbstractWidget 
    {
    public:
    
        SFMLWidget(ModelGamePtr& model);

        ~SFMLWidget() override = default;

        bool IsOpen() const override;

    protected:

        void UpdateWidget() override;

        void ProcessingEvents() override;

        void UpdateView(Model::DescriptionMap) override;

        void SetNextBlock(Model::DescriptionBlock) override;

        void SetScore(unsigned int) override;

    private:
        sf::RenderWindow _window;

        Controller::MoveController _controller;

        bool _windowOpen{true};
        SFMLMap _map;
        SFMLPreviewBlock _previwBlock;
        sf::Text _score;
        sf::Font _font;

        std::stack<sf::Event> _uievents;
    };
}
