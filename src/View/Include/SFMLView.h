#pragma once

#include "AbstractObserver.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>



namespace Tetris::View
{

    class SFMLView: public Common::AbstarctObserver
    {
    public:

        void update();

    private:

        //sf::VertexArray triangle(sf::Triangles, 3);
    };
}
