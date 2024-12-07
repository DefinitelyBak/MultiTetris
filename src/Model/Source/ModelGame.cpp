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

    ModelGame::~ModelGame()
    {
		SignalCloseViews();
    }

    void ModelGame::SlotUpdate(Command command)
    {
		DescriptionModel descriptionModel;

		{
			std::lock_guard<std::mutex> l(_mutex);
			if (_map.IsFullMap())
			{
				_map.Restart();
				_score = 0;
				descriptionModel.score = _score;
			}

			if(!_map.HasActiveBlock())
			{
				_currentBlock = _nextBlock;
				_nextBlock = CreateRandomBlock();
				_map.SetBlock(_currentBlock);
				descriptionModel.nextBlock = DescriptionBlock(_nextBlock->GetType(), _nextBlock->GetColor());
			}

			_map.MoveBlock(command);
	
			if (auto deletedLines = _map.GetCountDeletedLines(); deletedLines)
			{
				AddScore(deletedLines);
				descriptionModel.score = _score;
			}

			descriptionModel.map = _map.GetMap();
			descriptionModel.size = _map.GetSize(); 
		}

		SignalUpdateView(descriptionModel);
    }

    void ModelGame::SetView(AbstractWidgetPtr view)
    {
		DescriptionModel descriptionModel;
		std::optional<DescriptionBlock> descriptionBlock;
		std::optional<unsigned int> newScore;

		{
			std::lock_guard<std::mutex> l(_mutex);
			SignalUpdateView.connect(boost::signals2::signal<void(Model::DescriptionModel)>::slot_type
				(&AbstractWidget::SlotUpdateView, view.get(), boost::placeholders::_1).track_foreign(view));

			SignalCloseViews.connect(boost::signals2::signal<void()>::slot_type
				(boost::bind(&AbstractWidget::SlotCLoseEvent, view.get())).track_foreign(view));

			descriptionModel.map = _map.GetMap();
			descriptionModel.size = _map.GetSize();
			descriptionModel.nextBlock = DescriptionBlock(_nextBlock->GetType(), _nextBlock->GetColor()); 
			descriptionModel.score = _score;
		}

		SignalUpdateView(descriptionModel);
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