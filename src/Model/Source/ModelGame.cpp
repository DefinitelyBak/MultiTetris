#include "ModelGame.h"

#include "Commands/MoveCommand.h"
#include "Commands/UpdateMapCommand.h"


namespace Tetris::Model
{

    ModelGame::ModelGame(): Tetris::Common::AbstractObservable(), Tetris::Common::AbstarctObserver(), _rng(_dev()), _dist7(0,6), _dist5(0,4)
	{
		_factory.add<Iblock>(IdShape::Iblock);
        _factory.add<Jblock>(IdShape::Jblock);
        _factory.add<Lblock>(IdShape::Lblock);
        _factory.add<Oblock>(IdShape::Oblock);
        _factory.add<Sblock>(IdShape::Sblock);
        _factory.add<Tblock>(IdShape::Tblock);
        _factory.add<Zblock>(IdShape::Zblock);

		_map.SetNewBlock(CreateRandomBlock());
	}

    void ModelGame::Update()
	{
		Common::AbstractCommandPtr newCommand;

		if(!GetCommand(newCommand))
			return;

		if(newCommand->GetType() == CommonType::MoveBlock)
		{
			auto moveCommand = std::dynamic_pointer_cast<MoveCommand>(newCommand);

			if(!moveCommand)
				return;

			if(!_map.HasActiveBlock())
				_map.SetNewBlock(CreateRandomBlock());

			_map.MoveBlock(moveCommand->GetTypeCommand());

			NotifyAll(std::make_shared<UpdateMapCommand>(_map.GetMap(),_map.GetSize()));
		}		
	}

	const std::shared_ptr<AbstractBlock> ModelGame::CreateRandomBlock()
	{
		static IdShape typesShapes[7] = {IdShape::Iblock, IdShape::Jblock, IdShape::Lblock, IdShape::Oblock, IdShape::Sblock, IdShape::Tblock, IdShape::Zblock};
		static Color typesColor[5] = {Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Orange};

		int typeShape = _dist7(_rng);
		int typeColor = _dist5(_rng);

		while(typesShapes[typeShape] == _lastTypeBlock)
			typeShape = _dist7(_rng);

		while(typesColor[typeColor] == _lasTypeColor)
			typeColor = _dist5(_rng);

		_lastTypeBlock = typesShapes[typeShape];
		_lasTypeColor = typesColor[typeColor];
		std::shared_ptr<AbstractBlock> result(_factory.Create(typesShapes[typeShape],typesColor[typeColor]));

		return result;
	}

}