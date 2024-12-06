#pragma once

#include "Precompile.h"

#include "SFML/Graphics/Text.hpp"


namespace Tetris::View
{
    class SFMLText : public sf::Text
    {
    public:
        SFMLText(std::string fondPath, sf::Color colorText, sf::Uint32 style);
   
    private:

        sf::Font _font;
    };

}