#include "SFML/Text.h"


namespace Tetris::View::SFML
{

    Text::Text(const std::string& fontPath, sf::Color colorText, sf::Uint32 style)
    {
        if (!_font.loadFromFile(fontPath))
            throw(std::invalid_argument("Invalid path to font"));

        setFont(_font);
        setFillColor(colorText);
        setStyle(style);
    }

}