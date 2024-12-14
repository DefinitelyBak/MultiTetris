#include "ModelGame.h"

#include "blocks/AbstractBlock.h"


namespace Tetris::Model
{

    ModelGame::ModelGame():_map(10, 22), _device(), _randomEngine(_device())
	{
		_factory.add<Iblock>(IdShape::Iblock);
        _factory.add<Jblock>(IdShape::Jblock);
        _factory.add<Lblock>(IdShape::Lblock);
        _factory.add<Oblock>(IdShape::Oblock);
        _factory.add<Sblock>(IdShape::Sblock);
        _factory.add<Tblock>(IdShape::Tblock);
        _factory.add<Zblock>(IdShape::Zblock);

		_nextBlock = CreateRandomBlock();
	}

    void ModelGame::UpdateModel(Command command, DescriptionModel &desc)
    {
		if (_map.IsFullMap())
		{
			_map.Restart();
			_score = 0;
			desc.score = _score;
		}

		if(!_map.HasActiveBlock())
		{
			_currentBlock = _nextBlock;
			_nextBlock = CreateRandomBlock();
			_map.SetBlock(_currentBlock);
			desc.nextBlock = DescriptionBlock(_nextBlock->GetType(), _nextBlock->GetColor());
		}

		_map.MoveBlock(command);
	
		if (auto deletedLines = _map.GetCountDeletedLines(); deletedLines)
		{
			AddScore(deletedLines);
			desc.score = _score;
		}

		desc.map = _map.GetMap();
		desc.size = _map.GetSize(); 
    }

    void ModelGame::EmitSugnals(DescriptionModel &desc)
    {
		SignalUpdateView(desc);
    }

    void ModelGame::SetSignals(AbstractWidgetPtr &view, DescriptionModel &desc)
    {
		std::optional<DescriptionBlock> descriptionBlock;
		std::optional<unsigned int> newScore;

		SignalUpdateView.connect(TypeSignalUpdateView::slot_type(&AbstractWidget::SlotUpdateView, view.get(), boost::placeholders::_1).track_foreign(view));
		SignalCloseViews.connect(TypeSignalCloseViews::slot_type(boost::bind(&AbstractWidget::SlotCLoseEvent, view.get())).track_foreign(view));

		desc.map = _map.GetMap();
		desc.size = _map.GetSize();
		desc.nextBlock = DescriptionBlock(_nextBlock->GetType(), _nextBlock->GetColor()); 
		desc.score = _score;
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

    AbstractBlockPtr ModelGame::CreateRandomBlock()
    {
		static const IdShape typesShapes[7] = {IdShape::Iblock, IdShape::Jblock, IdShape::Lblock, IdShape::Oblock, IdShape::Sblock, IdShape::Tblock, IdShape::Zblock}; //  IdShape::Tblock};//
		static const TypeColor typesColor[4] = {TypeColor::Red, TypeColor::Green, TypeColor::Yellow, TypeColor::Blue};

		std::uniform_int_distribution<int> randomTypeShape(0,6);
        std::uniform_int_distribution<int> randomTypeColor(0,3);

		int randomShape = randomTypeShape(_randomEngine);
		int randomColor = randomTypeColor(_randomEngine);

		while(typesShapes[randomShape] == _lastTypeBlock)
			randomShape = randomTypeShape(_randomEngine);

		while(typesColor[randomColor] == _lasTypeColor)
			randomColor = randomTypeColor(_randomEngine);

		_lastTypeBlock = typesShapes[randomShape];
		_lasTypeColor = typesColor[randomColor];
		AbstractBlockPtr result(_factory.Create(typesShapes[randomShape],typesColor[randomColor]));

		return result;
	}

}