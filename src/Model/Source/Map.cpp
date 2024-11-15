#include "Map.h"


namespace Tetris::Model
{

    Map::Map(size_t columns, size_t rows)
    {
        _size.columns = columns;
        _size.rows = rows;
        _data.resize(columns * rows, Color::None);
    }

    DataMap Map::GetMap() const
    {
        return _data;
    }

    MapSize Map::GetSize()
    {
        return _size;
    }

    void Map::SetBlock(std::unique_ptr<AbstractBlock> shape)
    {
        _activeBlock = std::move(shape);
        _positionBlock = Position(_size.columns/2, _size.rows/2 + 2);
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
                newPos = _positionBlock - Position(0, -1);
            else if ( cmn == Command::Right)
                newPos = _positionBlock - Position(1, 0);
            else if ( cmn == Command::Left)
                newPos = _positionBlock - Position(-1, 0);

            Positions newDescriptionBlock = _activeBlock->GeCurrentDescription()  + newPos;
            
            if (IsBlockCanMove(newDescriptionBlock))
            {
                _positionBlock = newPos;
                return;
            }

            if(cmn == Command::Down)
            {
                SetBlockOnMap();
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
                if(IsBlockCanMove(newDescriptionBlock + offset))
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

        for(int row = 0; row < _size.rows; ++row)
        {
            bool lineFull = true;

            for(int column = 0; column < _size.columns; ++column)
                if(_data[row * _size.columns + column] == Color::None)
                {
                    lineFull = false;
                    break;
                }

            if(!lineFull)
                continue;

            ++_deletedLine;

            for(int nextRow = row + 1; nextRow < _size.rows; ++nextRow)
                for(int column = 0; column < _size.columns; ++column)
                    _data[row * _size.columns + column] = _data[nextRow * _size.columns + column]; 
        }
    }

    bool Map::IsBlockCanMove(Positions cmn)
    {
        for(auto fill: cmn)
        {
            if(fill.first > _size.columns || fill.first < 0 ||
               fill.second > _size.rows || fill.second < 0)
                return false;

            if (_data[_size.columns * fill.second + fill.first] != Color::None)
                return false;
        }

        return true;
    }

    void Map::SetBlockOnMap()
    {
        for(auto fill :_positionBlock+ _activeBlock->GeCurrentDescription())
            _data[_size.columns * fill.second + fill.first] = _activeBlock->GetColor();

    }

} // namespace