#include "Qt/PreviewBlock.h"


namespace Tetris::View::Qt
{
    PreviewBlock::PreviewBlock(QWindow* parent, bool withBorder): Map(parent, withBorder)
    {}

    void PreviewBlock::SetBlock(Model::IdShape typeColor,  Model::TypeColor color)
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

        SetMap(map, rows, columns);
    }

    Model::IdShape PreviewBlock::GetType() const
    {
        return _typeShape;
    }
}