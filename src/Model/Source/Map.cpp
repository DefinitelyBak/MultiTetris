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
        std::vector<TypeColor> data(_data);
        if (_activeBlock)
            SetBlockOnMap(data);
        return std::vector<TypeColor>(data.begin(), data.end() - _size.columns);
    }

    MapSize Map::GetSize() const
    {
        return {_size.columns, _size.rows - 1};
    }

    bool Map::IsFullMap()
    {
        Position lastRow{0, _size.rows - 1};
        for (size_t i = 0; i < _size.columns; ++i)
            if (GetField(_data, lastRow + Position{i, 0}) != TypeColor::None)
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
            _positionBlock = Position(std::round(_size.columns / 2.0), _size.rows - 2);
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

        if (cmn == Command::RotateRight || cmn == Command::RotateLeft)
        {
            RotateBlock(cmn);
            return;
        }

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
    }

    unsigned int Map::GetCountDeletedLines() const
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

    bool Map::IsBlockCanMove(Positions cmn)
    {
        for (const auto& field : cmn)
        {
            if (field.x >= _size.columns || field.x < 0 || field.y >= _size.rows || field.y < 0)
                return false;

            if (GetField(_data, field) != TypeColor::None)
                return false;
        }

        return true;
    }

    void Map::SetBlockOnMap(std::vector<TypeColor>& map)
    {
        for (const auto& fild : _positionBlock + _activeBlock->GetCurrentDescription())
            GetField(map, fild) = _activeBlock->GetColor();
    }

    void Map::RotateBlock(Command cmn)
    {
        auto from = _activeBlock->GetCurrentState();
        auto to = _activeBlock->GetNextState(cmn);
        Positions newDescriptionBlock = _activeBlock->GetDescription(to);

        for (auto& offset : _activeBlock->GetOffsets(from, to))
        {
            if (IsBlockCanMove(_positionBlock + newDescriptionBlock + offset))
            {
                _activeBlock->RotateBlock(cmn);
                _positionBlock = _positionBlock + offset;
                return;
            }
        }
    }

    TypeColor& Map::GetField(std::vector<TypeColor>& map, const Position& pos)
    {
        return map.at(_size.columns * pos.y + pos.x);
    }

} // namespace Tetris::Model
