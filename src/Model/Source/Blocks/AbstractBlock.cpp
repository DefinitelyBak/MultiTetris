#include "blocks/AbstractBlock.h"


namespace Tetris::Model::Blocks
{

    AbstractBlock::AbstractBlock(TypeColor color) : _color(color) {}

    TypeColor AbstractBlock::GetColor() const
    {
        return _color; 
    }

    Positions AbstractBlock::GetCurrentDescription()
    {
        return _stateToPositions.at(_state);
    }

    Positions AbstractBlock::GetDescription(State state)
    {
        return _stateToPositions.at(state);
    }

    State AbstractBlock::GetCurrentState() const
    {
        return _state;
    }

    State AbstractBlock::GetNextState(Command cmd) const
    {
        switch (cmd)
        {
            case Command::RotateRight:
                switch (_state)
                {
                    case State::Up:    return State::Right;
                    case State::Right: return State::Down;
                    case State::Down:  return State::Left; 
                    case State::Left:  return State::Up; 
                    default:          return _state;
                }

            case Command::RotateLeft:
                switch (_state)
                {
                    case State::Up:    return State::Left;
                    case State::Left:  return State::Down;
                    case State::Down:  return State::Right; 
                    case State::Right: return State::Up; 
                    default:          return _state;
                }

            default:
                return _state;
        }
    }

    Offsets AbstractBlock::GetOffsets(State from, State to)
    {
        return _stateToOffset.at(from) - _stateToOffset.at(to);
    }

    void AbstractBlock::RotateBlock(Command cmd)
    {
        _state = GetNextState(cmd);
    }

} // namespace Tetris::Model::Blocks
