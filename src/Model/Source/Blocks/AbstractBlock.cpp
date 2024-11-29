#include "blocks/AbstractBlock.h"


namespace Tetris::Model::Blocks
{

	AbstractBlock::AbstractBlock(TypeColor color): _color(color){};

	TypeColor AbstractBlock::GetColor() const
	{
		return _color; 
	}

	Positions AbstractBlock::GeCurrentDescription()
	{
		return _stateToPositions[_state];
	}

	Positions AbstractBlock::GetDescription(State state)
	{
		return _stateToPositions[state];
	}

	State AbstractBlock::GeCurrentState() const
	{
		return _state;
	}

	State AbstractBlock::GetNextState(Command cmd) const
	{
		if(cmd == Command::RotateRight)
		{
			switch (_state)
			{
			case State::Up:
				return State::Right;
			case State::Right:
				return State::Down;
			case State::Down:
				return State::Left; 
			case State::Left:
				return State::Up; 
			default:
				return _state;
			}
		}
		else if(cmd == Command::RotateLeft)
		{
			switch (_state)
			{
			case State::Up:
				return State::Left;
			case State::Left:
				return State::Down;
			case State::Down:
				return State::Right; 
			case State::Right:
				return State::Up; 
			default:
				return _state;
			}
		}

		return _state;
	}

	Offsets AbstractBlock::GetOffsets(State from, State to)
	{
		return _stateToOffset[from] - _stateToOffset[to];
	}

	void AbstractBlock::RotateBlock(Command cmd)
	{
		_state = GetNextState(cmd);
	}

}