#include "ModelGame.h"

#include "blocks/Iblock.h"
#include "blocks/Jblock.h"
#include "blocks/Lblock.h"
#include "blocks/Oblock.h"
#include "blocks/Sblock.h"
#include "blocks/Tblock.h"
#include "blocks/Zblock.h"


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

    void ModelGame::UpdateModel(Command command, DescriptionModel &desc)
    {
        if (_map.IsFullMap())
        {
            ResetGame(desc);
        }

        if (!_map.HasActiveBlock())
        {
            SpawnNewBlock(desc);
        }

        _map.MoveBlock(command);
        UpdateScore(desc);
        desc.map = _map.GetMap();
        desc.size = _map.GetSize(); 
    }

    void ModelGame::ResetGame(DescriptionModel &desc)
    {
        _map.Restart();
        _score = 0;
        desc.score = _score;
    }

    void ModelGame::SpawnNewBlock(DescriptionModel &desc)
    {
        _currentBlock = _nextBlock;
        _nextBlock = CreateRandomBlock();
        _map.SetBlock(_currentBlock);
        desc.nextBlock = _nextBlock;
    }

    void ModelGame::UpdateScore(DescriptionModel &desc)
    {
        if (auto deletedLines = _map.GetCountDeletedLines(); deletedLines)
        {
            AddScore(deletedLines);
            desc.score = _score;
        }
    }

    void ModelGame::AddScore(unsigned int lines)
    {
        static const std::array<int, 5> scorePoints = {0, 100, 300, 700, 1500};
        if (lines > 0 && lines <= 4)
        {
            _score += scorePoints[lines];
        }
        else if (lines > 4)
        {
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

        if (withoutBlock == nullptr)
        {
            return CreateBlock(allTypesBlocks, allTypesColor);
        }

        return CreateBlockExcluding(withoutBlock, allTypesBlocks, allTypesColor);
    }

    AbstractBlockPtr ModelGame::CreateBlock(const std::array<TypeBlock, 7>& blockTypes, const std::array<TypeColor, 4>& colorTypes)
    {
        int randomShape = std::uniform_int_distribution<int>(0, 6)(_randomEngine);
        int randomColor = std::uniform_int_distribution<int>(0, 3)(_randomEngine);
        return AbstractBlockPtr{_factory.Create(blockTypes[randomShape], colorTypes[randomColor])};
    }

    AbstractBlockPtr ModelGame::CreateBlockExcluding(AbstractBlockPtr withoutBlock, const std::array<TypeBlock, 7>& blockTypes, const std::array<TypeColor, 4>& colorTypes)
    {
        std::array<TypeBlock, 6> typesBlocks;
        std::array<TypeColor, 3> typesColor;

        FillExcludingArray(blockTypes, withoutBlock->GetType(), typesBlocks);
        FillExcludingArray(colorTypes, withoutBlock->GetColor(), typesColor);

        int randomShape = std::uniform_int_distribution<int>(0, 5)(_randomEngine);
        int randomColor = std::uniform_int_distribution<int>(0, 2)(_randomEngine);

        return AbstractBlockPtr{_factory.Create(typesBlocks[randomShape], typesColor[randomColor])};
    }

    template<typename T, size_t N>
    void ModelGame::FillExcludingArray(const std::array<T, N>& source, T excluded, std::array<T, N-1>& dest)
    {
        size_t index = 0;
        for (const auto& item : source)
        {
            if (item != excluded)
            {
                dest[index++] = item;
            }
        }
    }

} // namespace Tetris::Model
