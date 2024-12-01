#include "Map.h"

#include "Factory/ShapeFactory.h"
#include <cmath>

namespace Tetris::Model
{

    Map::Map(size_t columns, size_t rows)
    {
        _size.columns = columns;
        _size.rows = rows;
        _data.resize(columns * rows, TypeColor::None);
    }

    DataMap Map::GetMap()
    {
        DataMap data = _data;
        if(_activeBlock)
            SetBlockOnMap(data);
        return data;
    }

    MapSize Map::GetSize()
    {
        return _size;
    }

    void Map::SetBlock(std::shared_ptr<AbstractBlock> shape)
    {
        _activeBlock = shape;
        /// Тут надо смотреть на тип фигуры и выбирать смещение отсносительно начала
        _positionBlock = Position(std::round(_size.columns/2.0), _size.rows-1);
    }

    bool Map::HasActiveBlock()
    {
        return bool(_activeBlock);
    }

	void Map::MoveBlock(Command cmn)
    {
        if(!HasActiveBlock())
            return;

        if (cmn == Command::Down || cmn == Command::Right || cmn == Command::Left)
        {
            Position newPos;
            
            if ( cmn == Command::Down)
                newPos = _positionBlock - Position(0, 1);
            else if ( cmn == Command::Right)
                newPos = _positionBlock + Position(1, 0);
            else if ( cmn == Command::Left)
                newPos = _positionBlock - Position(1, 0);

            Positions newDescriptionBlock = newPos + _activeBlock->GeCurrentDescription();
            
            if (IsBlockCanMove(newDescriptionBlock))
            {
                _positionBlock = newPos;
                return;
            }

            if(cmn == Command::Down)
            {
                SetBlockOnMap(_data);
                _activeBlock = nullptr;
                DeleteLines();
                _deletedLine = GetCountDeletedLines();
            }

            return;
        }

        if(cmn == Command::RotateRight || cmn == Command::RotateLeft)
        {
            auto from = _activeBlock->GeCurrentState();
            auto to = _activeBlock->GetNextState(cmn);
            Positions newDescriptionBlock = _activeBlock->GetDescription(to);

            for(const auto& offset : _activeBlock->GetOffsets(from, to))
                if(IsBlockCanMove(_positionBlock + newDescriptionBlock + offset))
                {
                    _activeBlock->RotateBlock(cmn);
                    return;
                }
        }
    }

    unsigned int Map::GetCountDeletedLines()
    {
        return _deletedLine;
    }

    void Map::DeleteLines()
    {
        _deletedLine = 0;

        // Пройтись по всем строкам
        for(int row = 0; row < _size.rows; ++row)
        {
            bool lineFull = true;

            for(int column = 0; column < _size.columns; ++column)
            {
                if(_data[row * _size.columns + column] == TypeColor::None)
                {
                    lineFull = false;
                    break;
                }
            }

            if(!lineFull)
                continue;

            ++_deletedLine;

            for(int localRow = row; localRow < _size.rows - 1; ++localRow)
            {
                for(int column = 0; column < _size.columns; ++column)
                    _data[localRow * _size.columns + column] = _data[(localRow + 1) * _size.columns + column];
            }
            --row;
        }
    }

    bool Map::IsBlockCanMove(Positions cmn)
    {
        for(auto fill: cmn)
        {
            if(fill.first > _size.columns || fill.first < 1 ||
               fill.second > _size.rows || fill.second < 1)
                return false;

            if (_data[_size.columns * (fill.second - 1) + fill.first - 1] != TypeColor::None)
                return false;
        }

        return true;
    }

    void Map::SetBlockOnMap(DataMap& map)
    {
        for(auto fill : _positionBlock + _activeBlock->GeCurrentDescription())
            map[_size.columns * (fill.second-1) + fill.first - 1] = _activeBlock->GetColor();

    }

} // namespace