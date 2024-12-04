#include "SFMLPreviewBlock.h"

#include "SFML/Graphics/RenderTarget.hpp"


namespace Tetris::View
{
    SFMLPreviewBlock::SFMLPreviewBlock(sf::Vector2f windowSize, bool withBorder): _map(windowSize, withBorder)
    {}

    void SFMLPreviewBlock::SetType(Model::IdShape typeColor)
    {
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
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None}; // 4 строка
            break;

        case Model::IdShape::Jblock:
            rows = 4;
            columns = 5;
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None,  Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None}; // 4 строка
            break;

        case Model::IdShape::Lblock:
            rows = 4;
            columns = 5;
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None,  Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None}; // 4 строка
            break;

        case Model::IdShape::Oblock:
            rows = 4;
            columns = 4;
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None,
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None }; // 4 строка
            break;

        case Model::IdShape::Sblock:
            rows = 4;
            columns = 4;
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None}; // 4 строка
            break;

        case Model::IdShape::Tblock:
            rows = 4;
            columns = 4;
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::None, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None}; // 4 строка
            break;

        case Model::IdShape::Zblock:
            rows = 4;
            columns = 4;
            map = {Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, // 1 строка
                   Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::Green, Model::TypeColor::Green, Model::TypeColor::None, 
                   Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None, Model::TypeColor::None}; // 4 строка
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