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

		UpdateView(_map.GetMap(), _map.GetSize(), _score);
		
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

    std::unique_ptr<AbstractBlock> ModelGame::CreateRandomBlock()
    {
		static const IdShape typesShapes[7] = {IdShape::Iblock, IdShape::Jblock, IdShape::Lblock, IdShape::Oblock, IdShape::Sblock, IdShape::Tblock, IdShape::Zblock};
		static const Color typesColor[5] = {Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Orange};

		std::uniform_int_distribution<int> randomTypeShape(0,6);
        std::uniform_int_distribution<int> randomTypeColor(0,5);

		int typeShape = randomTypeShape(_randomEngine);
		int typeColor = randomTypeColor(_randomEngine);

		while(typesShapes[typeShape] == _lastTypeBlock)
			typeShape = randomTypeShape(_randomEngine);

		while(typesColor[typeColor] == _lasTypeColor)
			typeColor = randomTypeColor(_randomEngine);

		_lastTypeBlock = typesShapes[typeShape];
		_lasTypeColor = typesColor[typeColor];
		std::unique_ptr<AbstractBlock> result(_factory.Create(typesShapes[typeShape],typesColor[typeColor]));

		return result;
	}

}