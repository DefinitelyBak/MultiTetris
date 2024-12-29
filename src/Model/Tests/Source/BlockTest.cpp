#include <gtest/gtest.h>

#include <array>
#include <vector>

#include <Model/Factory/BlocksFactory.h>
#include <Model/blocks/Iblock.h>
#include <Model/blocks/Jblock.h>
#include <Model/blocks/Lblock.h>
#include <Model/blocks/Oblock.h>
#include <Model/blocks/Sblock.h>
#include <Model/blocks/Tblock.h>
#include <Model/blocks/Zblock.h>


namespace Tetris::Tests
{
    using namespace Model; 
    using namespace Model::Blocks;

    class BlockTest : public ::testing::Test 
    {
    protected:
        BlockTest()
        {
            _factory.add<Blocks::Iblock>(TypeBlock::Iblock);
            _factory.add<Blocks::Jblock>(TypeBlock::Jblock);
            _factory.add<Blocks::Lblock>(TypeBlock::Lblock);
            _factory.add<Blocks::Oblock>(TypeBlock::Oblock);
            _factory.add<Blocks::Sblock>(TypeBlock::Sblock);
            _factory.add<Blocks::Tblock>(TypeBlock::Tblock);
            _factory.add<Blocks::Zblock>(TypeBlock::Zblock);
        }

        Model::Blocks::BlocksFactory _factory;
    };

    TEST_F(BlockTest, blockColor)
    {
        AbstractBlockPtr block(_factory.Create(TypeBlock::Iblock, TypeColor::Green));
        ASSERT_EQ(block->GetColor(), TypeColor::Green);
    }

    TEST_F(BlockTest, statusBlockTurningClockwise)
    {
        AbstractBlockPtr block(_factory.Create(TypeBlock::Iblock, TypeColor::Green));
        ASSERT_EQ(block->GetCurrentState(), State::Up);

        for (int i = 0; i < 4; ++i)
        {
            ASSERT_EQ(block->GetNextState(Command::RotateRight), static_cast<State>((i + 1) % 4));
            block->RotateBlock(Command::RotateRight);
            ASSERT_EQ(block->GetCurrentState(), static_cast<State>((i + 1) % 4));
        }
    }

    TEST_F(BlockTest, statusBlockTurningCounterclockwise)
    {
        AbstractBlockPtr block(_factory.Create(TypeBlock::Iblock, TypeColor::Green));
        ASSERT_EQ(block->GetCurrentState(), State::Up);

        for (int i = 1; i < 5; ++i) {
            State debug = static_cast<State>((4 - i) % 4);
            ASSERT_EQ(block->GetNextState(Command::RotateLeft), static_cast<State>((4 - i) % 4));
            block->RotateBlock(Command::RotateLeft);
            ASSERT_EQ(block->GetCurrentState(), static_cast<State>((4 - i) % 4));
        }
    }

    void TestOffsets(std::shared_ptr<AbstractBlock> block, const std::vector<std::pair<State, State>>& states, const std::vector<Offsets>& expectedOffsets)
    {
        for (size_t i = 0; i < states.size(); ++i) {
            auto offset = block->GetOffsets(states[i].first, states[i].second);
            ASSERT_EQ(offset, expectedOffsets[i]);
        }
    }

    TEST_F(BlockTest, JLSTZOffsets)
    {
        AbstractBlockPtr Lblock(_factory.Create(TypeBlock::Lblock, TypeColor::Green));
        std::vector<std::pair<State, State>> states = {
            {State::Up, State::Right},
            {State::Right, State::Down},
            {State::Down, State::Left},
            {State::Left, State::Up}
        };
        std::vector<Offsets> expectedOffsets = {
            {Position(0,0), Position(-1,0), Position(-1,1), Position(0,-2), Position(-1,-2)},
            {Position(0,0), Position(1,0), Position(1,-1), Position(0,2), Position(1,2)},
            {Position(0,0), Position(1,0), Position(1,1), Position(0,-2), Position(1,-2)},
            {Position(0,0), Position(-1,0), Position(-1,-1), Position(0,2), Position(-1,2)}
        };
        TestOffsets(Lblock, states, expectedOffsets);
    }

    TEST_F(BlockTest, IOffsets)
    {
        AbstractBlockPtr Iblock(_factory.Create(TypeBlock::Iblock, TypeColor::Green));
        std::vector<std::pair<State, State>> states = {
            {State::Up, State::Right},
            {State::Right, State::Down},
            {State::Down, State::Left},
            {State::Left, State::Up}
        };
        std::vector<Offsets> expectedOffsets = {
            {Position(1,0), Position(-1,0), Position(2,0), Position(-1,-1), Position(2,2)},
            {Position(0,-1), Position(-1,-1), Position(2,-1), Position(-1,1), Position(2,-2)},
            {Position(-1,0), Position(1,0), Position(-2,0), Position(1,1), Position(-2,-2)},
            {Position(0,1), Position(1,1), Position(-2,1), Position(1,-1), Position(-2,2)}
        };
        TestOffsets(Iblock, states, expectedOffsets);
    }

    TEST_F(BlockTest, OOffsets)
    {
        AbstractBlockPtr Oblock(_factory.Create(TypeBlock::Oblock, TypeColor::Green));
        std::vector<std::pair<State, State>> states = {
            {State::Up, State::Right},
            {State::Right, State::Down},
            {State::Down, State::Left},
            {State::Left, State::Up}
        };
        std::vector<Offsets> expectedOffsets = {
            {Position(0,1), Position(0,1), Position(0,1), Position(0,1), Position(0,1)},
            {Position(1,0), Position(1,0), Position(1,0), Position(1,0), Position(1,0)},
            {Position(0,-1), Position(0,-1), Position(0,-1), Position(0,-1), Position(0,-1)},
            {Position(-1,0), Position(-1,0), Position(-1,0), Position(-1,0), Position(-1,0)}
        };
        TestOffsets(Oblock, states, expectedOffsets);
    }
}
