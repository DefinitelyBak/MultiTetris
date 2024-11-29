#include "ModelGame.h"



namespace Tetris::Model
{

    ModelGame::ModelGame():_map(), _device(), _randomEngine(_device())
	{
		_factory.add<Iblock>(IdShape::Iblock);
        _factory.add<Jblock>(IdShape::Jblock);
        _factory.add<Lblock>(IdShape::Lblock);
        _factory.add<Oblock>(IdShape::Oblock);
        _factory.add<Sblock>(IdShape::Sblock);
        _factory.add<Tblock>(IdShape::Tblock);
        _factory.add<Zblock>(IdShape::Zblock);

		_map.SetBlock(CreateRandomBlock());
	}

    void ModelGame::SlotUpdate(Command command)
    {
		if(!_map.HasActiveBlock())
			_map.SetBlock(CreateRandomBlock());

		_map.MoveBlock(command);

		unsigned int deletedLines = _map.GetCountDeletedLines();
		if (deletedLines)
			AddScore(deletedLines);
 
		SignalUpdateView(DescriptionMap(_map.GetMap(), _map.GetSize(), 1));
		
    }

    void ModelGame::AddScore(unsigned int lines)
    {
		switch (lines)
		{
		case 0:
			return;
		case 1:
			_score+= 100;
			break;
		case 2:
			_score+= 300;
			break;
		case 3:
			_score+= 700;
			break;
		default:
			_score+= 1500;
			break;
		}
    }

    std::shared_ptr<AbstractBlock> ModelGame::CreateRandomBlock()
    {
		static const IdShape typesShapes[7] = {IdShape::Iblock, IdShape::Jblock, IdShape::Lblock, IdShape::Oblock, IdShape::Sblock, IdShape::Tblock, IdShape::Zblock};
		static const TypeColor typesColor[4] = {TypeColor::Red, TypeColor::Green, TypeColor::Yellow, TypeColor::Blue};

		std::uniform_int_distribution<int> randomTypeShape(0,6);
        std::uniform_int_distribution<int> randomTypeColor(0,4);

		int randomShape = randomTypeShape(_randomEngine);
		int randomColor = randomTypeColor(_randomEngine);

		while(typesShapes[randomShape] == _lastTypeBlock)
			randomShape = randomTypeShape(_randomEngine);

		while(typesColor[randomColor] == _lasTypeColor)
			randomColor = randomTypeColor(_randomEngine);

		_lastTypeBlock = typesShapes[randomShape];
		_lasTypeColor = typesColor[randomColor];
		std::shared_ptr<AbstractBlock> result(_factory.Create(typesShapes[randomShape],typesColor[randomColor]));

		return result;
	}

}