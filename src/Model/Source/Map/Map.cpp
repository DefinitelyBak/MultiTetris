#include "Map/Map.h"


namespace Tetris::Model::Map
{

    Map::Map(size_t columns, size_t rows): _columns(columns), _rows(rows)
    {
        _data.resize(columns * rows);
    }

    Map::Map(const std::vector<Data::Color>& map, size_t columns, size_t rows): 
    _columns(columns), _rows(rows), _data(map)
    {}

    std::vector<Data::Color> Map::GetMap() const
    {
        return _data;
    }

    std::pair<size_t, size_t> Map::GetSize()
    {
        return std::pair<size_t, size_t>(_columns, _rows);
    }

    size_t Map::GetLastNotFreeLine() const
    {
        for(size_t row = 0; row < _rows; ++row)
            if (!CheckLine(row))
                return row;

        return _rows;
    }

    void Map::SetNewBlock(const std::shared_ptr<AbstractBlock> shape)
    {
        _activeBlock = shape;
        _positionBlock = Position(_columns/2, _rows/2 + 2);
    }

    bool Map::HasActiveBlock() const
    {
        return _activeBlock.get();
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
            
            if (CheckMoveBlock(newDescriptionBlock))
            {
                _positionBlock = newPos;
                return;
            }

            if(cmn == Command::Down)
            {
                SetBlockOnMap();
                _deletedLine = DeleteLines();
            }

            return;
        }

        if(cmn == Command::RotateRight || cmn == Command::RotateLeft)
        {
            auto from = _activeBlock->GeCurrentState();
            auto to = _activeBlock->GetNextState(cmn);

            Positions newDescriptionBlock = _activeBlock->GetDescription(to);

            for(const auto& offset : _activeBlock->GetOffsets(from, to))
                if(CheckMoveBlock(newDescriptionBlock + offset))
                {
                    _activeBlock->RotateBlock(cmn);
                    return;
                }
        }

    }

} // namespace