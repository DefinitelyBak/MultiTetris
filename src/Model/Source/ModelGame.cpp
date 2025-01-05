#include <Model/ModelGame.h>

#include <Model/Blocks/Iblock.h>
#include <Model/Blocks/Jblock.h>
#include <Model/Blocks/Lblock.h>
#include <Model/Blocks/Oblock.h>
#include <Model/Blocks/Sblock.h>
#include <Model/Blocks/Tblock.h>
#include <Model/Blocks/Zblock.h>


namespace Tetris::Model
{

    ModelGame::ModelGame() : _map(10, 22), _device(), _randomEngine(_device())
    {
        RegisterBlocks();
        _nextBlock = CreateRandomBlock();
    }

    void ModelGame::RegisterBlocks()
    {
        _factory.add<Blocks::Iblock>(TypeBlock::Iblock);
        _factory.add<Blocks::Jblock>(TypeBlock::Jblock);
        _factory.add<Blocks::Lblock>(TypeBlock::Lblock);
        _factory.add<Blocks::Oblock>(TypeBlock::Oblock);
        _factory.add<Blocks::Sblock>(TypeBlock::Sblock);
        _factory.add<Blocks::Tblock>(TypeBlock::Tblock);
        _factory.add<Blocks::Zblock>(TypeBlock::Zblock);
    }

    MementoModelPtr ModelGame::UpdateModel(Command command)
    {
        if (_map.IsFull())
            ResetGame();
        if (!_map.HasActiveBlock())
            SpawnNewBlock();

        _map.MoveBlock(command);

        if (_map.GetCountDeletedLines() > 0)
            UpdateScore();

        return MakeMementoModel();
    }

    void ModelGame::ResetGame()
    {
        _map.Restart();
        _score = 0;
    }

    void ModelGame::SpawnNewBlock()
    {
        _currentBlock = _nextBlock;
        _nextBlock = CreateRandomBlock(_nextBlock);
        _map.SetBlock(_currentBlock);
    }

    MementoModelPtr ModelGame::MakeMementoModel()
    {
        MementoModelPtr desc = std::make_shared<Model::MementoModel>();
        desc->map = _map.GetMap();
        desc->size = _map.GetSize();
        desc->nextBlock = _nextBlock;
        desc->score = _score;

        return desc;
    }

    void ModelGame::UpdateScore()
    {
        static const std::array<int, 5> scorePoints = { 0, 100, 300, 700, 1500 };

        if (auto deletedLines = _map.GetCountDeletedLines(); deletedLines)
        {
            if (deletedLines > 0 && deletedLines <= 4)
                _score += scorePoints[deletedLines];
            else if (deletedLines > 4)
                _score += scorePoints[4];
        }
    }

    AbstractBlockPtr ModelGame::CreateRandomBlock(AbstractBlockPtr withoutBlock)
    {
        static const std::array<TypeBlock, 7> allTypesBlocks = {
            TypeBlock::Iblock, TypeBlock::Jblock, TypeBlock::Lblock,
            TypeBlock::Oblock, TypeBlock::Sblock, TypeBlock::Tblock,
            TypeBlock::Zblock
        };
        static const std::array<TypeColor, 4> allTypesColor = {
            TypeColor::Red, TypeColor::Green, TypeColor::Yellow, TypeColor::Blue
        };

        int randomShape = std::uniform_int_distribution<int>(0, 6)(_randomEngine);
        int randomColor = std::uniform_int_distribution<int>(0, 3)(_randomEngine);

        if (withoutBlock)
        {
            if (withoutBlock->GetColor() == allTypesColor[randomColor]) randomColor = (randomColor + 1) % allTypesColor.size();
            if (withoutBlock->GetType() == allTypesBlocks[randomShape]) randomShape = (randomShape + 1) % allTypesBlocks.size();
        }

        return AbstractBlockPtr{ _factory.Create(allTypesBlocks[randomShape], allTypesColor[randomColor]) };
    }

} // namespace Tetris::Model
