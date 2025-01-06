#include <Model/Blocks/AbstractBlock.h>


namespace Tetris::Model::Blocks
{

    AbstractBlock::AbstractBlock(TypeColor color) : _color(color) {}

    TypeColor AbstractBlock::GetColor() const
    {
        return _color; 
    }

    TypeBlock AbstractBlock::GetType() const
    {
        return TypeBlock::None;
    }

    Positions AbstractBlock::GetFields(std::optional<Orientation> orientation) const
    {
        if(orientation)
            return _orientationToPositions.at(orientation.value());
        return _orientationToPositions.at(_orientation);
    }

    Orientation AbstractBlock::GetOrientatio(std::optional<Command> cmd) const
    {
        if (cmd)
        {
            switch (cmd.value())
            {
            case Command::RotateRight:
                switch (_orientation)
                {
                case Orientation::Up:    return Orientation::Right;
                case Orientation::Right: return Orientation::Down;
                case Orientation::Down:  return Orientation::Left;
                case Orientation::Left:  return Orientation::Up;
                default:          return _orientation;
                }

            case Command::RotateLeft:
                switch (_orientation)
                {
                case Orientation::Up:    return Orientation::Left;
                case Orientation::Left:  return Orientation::Down;
                case Orientation::Down:  return Orientation::Right;
                case Orientation::Right: return Orientation::Up;
                default:          return _orientation;
                }

            default:
                return _orientation;
            }
        }
        return _orientation;
    }

    Offsets AbstractBlock::GetOffsets(Orientation from, Orientation to) const
    {
        return _orientationToOffset.at(from) - _orientationToOffset.at(to);
    }

    void AbstractBlock::RotateBlock(Command cmd)
    {
        _orientation = GetOrientatio(cmd);
    }

} // namespace Tetris::Model::Blocks
