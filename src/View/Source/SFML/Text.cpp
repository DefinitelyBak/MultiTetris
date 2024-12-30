#include <View/SFML/Text.h>


namespace Tetris::View::SFML
{

    Text::Text(const std::string& fontPath, sf::Color colorText, std::uint32_t style): sf::Text(_font)
    {
        if (!_font.openFromFile(fontPath))
            throw(std::invalid_argument("Invalid path to font"));

        setFont(_font);
        setFillColor(colorText);
        setStyle(style);
    }

}