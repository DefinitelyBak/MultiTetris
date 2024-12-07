#include "SFML/SFMLText.h"


namespace Tetris::View
{

    SFMLText::SFMLText(std::string fondPath, sf::Color colorText, sf::Uint32 style)
    {
        if (!_font.loadFromFile(fondPath))
        {
            throw(std::invalid_argument("Invalid path to font"));
        }

        setFont(_font);
        setFillColor(colorText);
        setStyle(style);
    }

}