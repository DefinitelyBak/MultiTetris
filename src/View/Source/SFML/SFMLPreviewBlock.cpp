#include "SFML/SFMLPreviewBlock.h"


namespace Tetris::View
{
    SFMLPreviewBlock::SFMLPreviewBlock(sf::Vector2f windowSize, bool withBorder): _map(windowSize, withBorder)
    {}

    void SFMLPreviewBlock::SetBlock(Model::IdShape typeColor,  Model::TypeColor color)
    {
        using Model::TypeColor::None;

        if (typeColor == _typeShape)
            return;
        
        Model::DataMap map;
        int rows;
        int columns;

        switch (typeColor)
        {
        case Model::IdShape::Iblock:
            rows = 4;
            columns = 6;
            map = {None, None, None, None, None, None, // 1 строка
                   None, None, None, None, None, None,
                   None, color, color, color, color, None,
                   None, None, None, None, None, None}; // 4 строка
            break;

        case Model::IdShape::Jblock:
            rows = 4;
            columns = 5;
            map = {None, None, None, None,  None, // 1 строка
                   None, color, color, color, None,
                   None, color, None, None, None,
                   None, None, None, None, None}; // 4 строка
            break;

        case Model::IdShape::Lblock:
            rows = 4;
            columns = 5;
            map = {None, None, None, None,  None, // 1 строка
                   None, color, color, color, None,
                   None, None, None, color, None,
                   None, None, None, None, None}; // 4 строка
            break;

        case Model::IdShape::Oblock:
            rows = 4;
            columns = 4;
            map = {None, None, None, None, // 1 строка
                   None, color, color, None,
                   None, color, color, None, 
                   None, None, None, None }; // 4 строка
            break;

        case Model::IdShape::Sblock:
            rows = 4;
            columns = 5;
            map = {None, None, None, None, None, // 1 строка
                   None, color, color, None, None, 
                   None, None, color, color, None, 
                   None, None, None, None, None}; // 4 строка
            break;

        case Model::IdShape::Tblock:
            rows = 4;
            columns = 5;
            map = {None, None, None, None, None, // 1 строка
                   None, color, color,color, None, 
                   None, None, color, None, None, 
                   None, None, None, None, None}; // 4 строка
            break;

        case Model::IdShape::Zblock:
            rows = 4;
            columns = 5;
            map = {None, None, None, None, None, // 1 строка
                   None, None, color, color, None, 
                   None, color, color, None, None, 
                   None, None, None, None, None}; // 4 строка
            break;
        default:
            break;
        }

        _map.SetMap(map, rows, columns);
    }

    Model::IdShape SFMLPreviewBlock::GetType() const
    {
        return _typeShape;
    }

    void SFMLPreviewBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(_map, states);
    }
}