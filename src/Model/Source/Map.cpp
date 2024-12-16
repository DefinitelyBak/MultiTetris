#include "Map.h"
#include "Factory/BlocksFactory.h"


namespace Tetris::Model
{

    Map::Map(size_t columns, size_t rows)
    {
        _size.columns = columns;
        _size.rows = rows + 1; // Увеличиваем на 1 для учета верхней границы
        _data.resize(_size.columns * _size.rows, TypeColor::None);
    }

    std::vector<TypeColor> Map::GetMap()
    {
        std::vector<TypeColor> data(_data.begin() + _size.columns, _data.end());
        if (_activeBlock)
            SetBlockOnMap(data);
        return data;
    }

    MapSize Map::GetSize() const
    {
        return {_size.columns, _size.rows - 1};
    }

    bool Map::IsFullMap() const
    {
        for (size_t i = 0; i < _size.columns; ++i)
            if (_data[(_size.rows - 1) * _size.columns + i] != TypeColor::None)
                return true;

        return false;
    }

    void Map::Restart()
    {
        std::fill(_data.begin(), _data.end(), TypeColor::None);
        _activeBlock = nullptr;
        _deletedLine = 0;
    }

    void Map::SetBlock(AbstractBlockPtr shape)
    {
        if (shape->GetType() != TypeBlock::None)
        {
            _activeBlock = shape;
            _positionBlock = Position(std::round(_size.columns / 2.0), _size.rows - 1);
        }
    }

    bool Map::HasActiveBlock() const
    {
        return _activeBlock != nullptr;
    }

    void Map::MoveBlock(Command cmn)
    {
        if (!HasActiveBlock())
            return;

        _deletedLine = 0;

        Position newPos = _positionBlock;

        if (cmn == Command::Down)
            newPos.y -= 1;
        else if (cmn == Command::Right)
            newPos.x += 1;
        else if (cmn == Command::Left)
            newPos.x -= 1;

        Positions newDescriptionBlock = newPos + _activeBlock->GetCurrentDescription();

        if (IsBlockCanMove(newDescriptionBlock))
        {
            _positionBlock = newPos;
            return;
        }

        if (cmn == Command::Down)
        {
            SetBlockOnMap(_data);
            _activeBlock = nullptr;
            DeleteLines();
        }

        if (cmn == Command::RotateRight || cmn == Command::RotateLeft)
        {
            auto from = _activeBlock->GetCurrentState();
            auto to = _activeBlock->GetNextState(cmn);
            Positions newDescriptionBlock = _activeBlock->GetDescription(to);

            for (const auto& offset : _activeBlock->GetOffsets(from, to))
                if (IsBlockCanMove(_positionBlock + newDescriptionBlock + offset))
                {
                    _activeBlock->RotateBlock(cmn);
                    return;
                }
        }
    }

    unsigned int Map::GetCountDeletedLines() const // Исправлено: добавлен const
    {
        return _deletedLine;
    }

void Map::DeleteLines()
{
    for (int row = 0; row < _size.rows; ++row)
    {
        bool lineFull = std::all_of(_data.begin() + row * _size.columns, 
                                     _data.begin() + (row + 1) * _size.columns,
                                     [](TypeColor color) { return color != TypeColor::None; });

        if (lineFull)
        {
            ++_deletedLine;

            for (int localRow = row; localRow < _size.rows - 1; ++localRow)
            {
                std::copy(_data.begin() + (localRow + 1) * _size.columns,
                          _data.begin() + (localRow + 2) * _size.columns,
                          _data.begin() + localRow * _size.columns);
            }
            --row;
        }
    }
}


    bool Map::IsBlockCanMove(Positions cmn) const
    {
        for (const auto& fill : cmn)
        {
            if (fill.x >= _size.columns || fill.x < 1 ||
                fill.y >= _size.rows || fill.y < 1)
                return false;

            if (_data[_size.columns * (fill.y - 1) + fill.x - 1] != TypeColor::None)
                return false;
        }

        return true;
    }

    void Map::SetBlockOnMap(std::vector<TypeColor>& map) // Исправлено: передаем по ссылке
    {
        for (const auto& fill : _positionBlock + _activeBlock->GetCurrentDescription())
            map[_size.columns * (fill.y - 1) + fill.x - 1] = _activeBlock->GetColor();
    }

} // namespace Tetris::Model
