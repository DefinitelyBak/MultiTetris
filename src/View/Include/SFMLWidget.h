#pragma once

#include <SFML/Graphics.hpp>


#include "wigwag/life_token.hpp"
#include "ModelGame.h"
#include "MoveController.h"

#include "Types.h"


namespace Tetris::View
{
    using namespace Model;

    class SFMLWidget
    {
    public:
    
        SFMLWidget(/*std::shared_ptr<wigwag::thread_task_executor>& uiThread,*/ ModelGame& model);

        void Update();

        void SlotUpdate(DataMap map, MapSize size, unsigned int score);

    private:

        sf::RenderWindow _window;

        Controller::MoveController _controller;

        bool _windowOpen{true};

        wigwag::token _token;
        //sf::VertexArray triangle(sf::Triangles, 3);
    };
}
