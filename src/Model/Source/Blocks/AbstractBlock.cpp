#include "Blocks/AbstractBlock.h"


namespace Tetris::Model::Blocks
{

	AbstractBlock::AbstractBlock(Common::Data::Color color): _color(color){};

    AbstractBlock::DescriptionFigure AbstractBlock::GetDescription()
	{
        if (_positionToDescription.contains(_state))
            return _positionToDescription[_state];

        return AbstractBlock::DescriptionFigure();
    };

    AbstractBlock::State AbstractBlock::GetState() const
    {
        return _state;
    };

	Common::Data::Color AbstractBlock::GetColor() const
	{
		return _color;
	};

    void AbstractBlock::RotateShape()
    {
		if(!_positionToDescription.contains(_state))
			return;
		
		ChangeState(_state);
	};

    AbstractBlock::DescriptionFigure AbstractBlock::TryRotateShape() 
	{
		State state = _state;
		ChangeState(state);

		if(_positionToDescription.contains(state))
			return _positionToDescription[state];

		return AbstractBlock::DescriptionFigure();
	};

    void AbstractBlock::ChangeState(State& state)
	{
		switch (state)
		{
		case State::Left:
			state = State::Up;
			break;
		case State::Up:
			state = State::Right;
			break;				
		case State::Right:
			state = State::Down;
			break;
		case State::Down:
			state = State::Left;
			break;
		default:
			break;
		}
    };

}