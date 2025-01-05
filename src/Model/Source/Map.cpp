#include <Model/Map.h>
#include <Model/Factory/BlocksFactory.h>


namespace Tetris::Model
{

    Map::Map(size_t columns, size_t rows)
    {
        _size = { rows + 1, columns }; // Увеличиваем на 1 для учета верхней границы
        _data.resize(_size.rows * _size.columns, TypeColor::None);
    }

    std::vector<TypeColor> Map::GetMap() const
    {
        std::vector<TypeColor> data(_data.begin(), _data.end() - _size.columns);
        if (_activeBlock)
            SetBlockOnMap(data, { _size.rows - 1, _size.columns });
        return data;
    }

    MapSize Map::GetSize() const
    {
        return {_size.rows - 1, _size.columns, };
    }

    bool Map::IsFull()
    {
        return std::any_of(_data.begin() + (_size.rows - 1) * _size.columns,
                           _data.begin() + _size.rows * _size.columns,
                           [](TypeColor field) {return field != TypeColor::None; });
    }

    void Map::Restart()
    {
        std::fill(_data.begin(), _data.end(), TypeColor::None);
        _activeBlock = nullptr;
        _deletedLine = 0;
    }

    void Map::SetBlock(AbstractBlockPtr shape)
    {
        if (shape->GetType() == TypeBlock::None)
            return;
        
        _activeBlock = shape;
        _positionBlock = Position(std::round(_size.columns / 2.0), _size.rows - 2);
    }

    bool Map::HasActiveBlock() const
    {
        return _activeBlock.get();
    }

    void Map::MoveBlock(Command cmn)
    {
        _deletedLine = 0;
        if (!HasActiveBlock())
            return;

        if (cmn == Command::RotateRight || cmn == Command::RotateLeft)
            RotateBlock(cmn);

        if (cmn == Command::Down || cmn == Command::Right || cmn == Command::Left)
            PlaneParallelMotion(cmn);
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

            if (GetField(_data, _size, field) != TypeColor::None)
                return false;
        }

        return true;
    }

    void Map::SetBlockOnMap(std::vector<TypeColor>& map, MapSize size) const
    {
        for (const auto& field : _positionBlock + _activeBlock->GetFields())
        {
            if (field.x >= size.columns || field.x < 0 || field.y >= size.rows || field.y < 0)
                continue;

            GetField(map, size, field) = _activeBlock->GetColor();
        }
    }

    void Map::RotateBlock(Command cmn)
    {
        auto from = _activeBlock->GetOrientatio();
        auto to = _activeBlock->GetOrientatio(cmn);
        Positions descriptionBlock = _positionBlock + _activeBlock->GetFields(to);

        for (const auto& offset : _activeBlock->GetOffsets(from, to))
        {
            if (IsBlockCanMove(descriptionBlock + offset))
            {
                _activeBlock->RotateBlock(cmn);
                _positionBlock = _positionBlock + offset;
                return;
            }
        }
    }

    void Map::PlaneParallelMotion(Command cmn)
    {
        Position newPos = _positionBlock;
        if (cmn == Command::Down)
            newPos.y -= 1;
        else if (cmn == Command::Right)
            newPos.x += 1;
        else if (cmn == Command::Left)
            newPos.x -= 1;

        if (IsBlockCanMove(newPos + _activeBlock->GetFields()))
           _positionBlock = newPos;
        else if (cmn == Command::Down)
        {
            SetBlockOnMap(_data, _size);
            _activeBlock = nullptr;
            DeleteLines();
        }
    }

    TypeColor& Map::GetField(std::vector<TypeColor>& map, MapSize size, const Position& pos)
    {
        return map.at(pos.y * size.columns + pos.x);
    }

} // namespace Tetris::Model
