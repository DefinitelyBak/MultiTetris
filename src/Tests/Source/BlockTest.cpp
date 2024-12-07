#include <gtest/gtest.h>

#include "Precompile.h"

#include "Factory/BlocksFactory.h"


namespace Tetris::Tests
{

    using namespace Model; 
    using namespace Model::Blocks;

    class BlockTest : public ::testing::Test 
    {
    protected:
        BlockTest()
        {
            _factory.add<Iblock>(IdShape::Iblock);
            _factory.add<Jblock>(IdShape::Jblock);
            _factory.add<Lblock>(IdShape::Lblock);
            _factory.add<Oblock>(IdShape::Oblock);
            _factory.add<Sblock>(IdShape::Sblock);
            _factory.add<Tblock>(IdShape::Tblock);
            _factory.add<Zblock>(IdShape::Zblock);
        }

        Model::Blocks::BlocksFactory _factory;
    };

    TEST_F(BlockTest, blockColor)
    {
        std::shared_ptr<AbstractBlock> block(_factory.Create(IdShape::Iblock, TypeColor::Green));

        ASSERT_TRUE(block->GetColor() == TypeColor::Green);
    }

    TEST_F(BlockTest, statusBlockTurningClockwise)
    {
        std::shared_ptr<AbstractBlock> block(_factory.Create(IdShape::Iblock, TypeColor::Green));
        
        ASSERT_TRUE(block->GeCurrentState() == State::Up);

        ASSERT_TRUE(block->GetNextState(Command::RotateRight) == State::Right);
        block->RotateBlock(Command::RotateRight);
        ASSERT_TRUE(block->GeCurrentState() == State::Right);

        ASSERT_TRUE(block->GetNextState(Command::RotateRight) == State::Down);
        block->RotateBlock(Command::RotateRight);
        ASSERT_TRUE(block->GeCurrentState() == State::Down);

        ASSERT_TRUE(block->GetNextState(Command::RotateRight) == State::Left);
        block->RotateBlock(Command::RotateRight);
        ASSERT_TRUE(block->GeCurrentState() == State::Left);

        ASSERT_TRUE(block->GetNextState(Command::RotateRight) == State::Up);
        block->RotateBlock(Command::RotateRight);
        ASSERT_TRUE(block->GeCurrentState() == State::Up);
    }

    TEST_F(BlockTest, statusBlockTurningCounterclockwise)
    {
        std::shared_ptr<AbstractBlock> block(_factory.Create(IdShape::Iblock, TypeColor::Green));
        
        ASSERT_TRUE(block->GeCurrentState() == State::Up);

        ASSERT_TRUE(block->GetNextState(Command::RotateLeft) == State::Left);
        block->RotateBlock(Command::RotateLeft);
        ASSERT_TRUE(block->GeCurrentState() == State::Left);

        ASSERT_TRUE(block->GetNextState(Command::RotateLeft) == State::Down);
        block->RotateBlock(Command::RotateLeft);
        ASSERT_TRUE(block->GeCurrentState() == State::Down);

        ASSERT_TRUE(block->GetNextState(Command::RotateLeft) == State::Right);
        block->RotateBlock(Command::RotateLeft);
        ASSERT_TRUE(block->GeCurrentState() == State::Right);

        ASSERT_TRUE(block->GetNextState(Command::RotateLeft) == State::Up);
        block->RotateBlock(Command::RotateLeft);
        ASSERT_TRUE(block->GeCurrentState() == State::Up);
    }

    TEST_F(BlockTest, JLSTZOffsets)
    {
        std::shared_ptr<AbstractBlock> Lblock(_factory.Create(IdShape::Lblock, TypeColor::Green));
        
        // Up -> Right: ( 0, 0), (-1, 0), (-1,+1), ( 0,-2), (-1,-2). 
        Offsets templateOffset = {Position(0,0), Position(-1,0), Position(-1,1), Position(0,-2), Position(-1,-2)};
        auto offset = Lblock->GetOffsets(State::Up, State::Right);

        ASSERT_TRUE(templateOffset == offset);

        // Right -> Down: ( 0, 0), (1, 0), (1,-1), ( 0,2), (1,2). 
        templateOffset = {Position(0,0), Position(1,0), Position(1,-1), Position(0,2), Position(1,2)};
        offset = Lblock->GetOffsets(State::Right, State::Down);

        ASSERT_TRUE(templateOffset == offset);

        // Down -> Left: ( 0, 0), (1, 0), (1,1), ( 0, -2), (1,-2).
        templateOffset = {Position(0,0), Position(1,0), Position(1,1), Position(0,-2), Position(1,-2)};
        offset = Lblock->GetOffsets(State::Down, State::Left);

        ASSERT_TRUE(templateOffset == offset);

        // Left -> Up: ( 0, 0), (-1, 0), (-1,-1), ( 0, 2), (-1,2).
        templateOffset = {Position(0,0), Position(-1,0), Position(-1,-1), Position(0,2), Position(-1,2)};
        offset = Lblock->GetOffsets(State::Left, State::Up);

        ASSERT_TRUE(templateOffset == offset);
    }

    TEST_F(BlockTest, IOffsets)
    {
        std::shared_ptr<AbstractBlock> Iblock(_factory.Create(IdShape::Iblock, TypeColor::Green));
        
        // Up -> Right: ( 1, 0), (-1, 0), (2,0), ( -1,-1), (2,2).
        Offsets templateOffset = {Position(1,0), Position(-1,0), Position(2,0), Position(-1,-1), Position(2,2)};
        auto offset = Iblock->GetOffsets(State::Up, State::Right);

        ASSERT_TRUE(templateOffset == offset);

        // Right -> Down: ( 0, -1), (-1, -1), (2,-1), ( -1,1), (2,-2).
        templateOffset = {Position(0,-1), Position(-1,-1), Position(2,-1), Position(-1,1), Position(2,-2)};
        offset = Iblock->GetOffsets(State::Right, State::Down);

        ASSERT_TRUE(templateOffset == offset);

        // Down -> Left: ( -1, 0), (1, 0), (-2,0), ( 1,1), (-2,-2).
        templateOffset = {Position(-1,0), Position(1,0), Position(-2,0), Position(1,1), Position(-2,-2)};
        offset = Iblock->GetOffsets(State::Down, State::Left);

        ASSERT_TRUE(templateOffset == offset);

        // Left -> Up: ( 0, 1), (1, 1), (-2,1), ( 1,-1), (-2,2).
        templateOffset = {Position(0,1), Position(1,1), Position(-2,1), Position(1,-1), Position(-2,2)};
        offset = Iblock->GetOffsets(State::Left, State::Up);

        ASSERT_TRUE(templateOffset == offset);
    }

    TEST_F(BlockTest, OOffsets)
    {
        std::shared_ptr<AbstractBlock> Oblock(_factory.Create(IdShape::Oblock, TypeColor::Green));
        
        // Up -> Right: ( 0, 1), ( 0, 1), ( 0, 1), ( 0, 1), ( 0, 1).
        Offsets templateOffset = {Position(0,1), Position(0,1), Position(0,1), Position(0,1), Position(0,1)};
        auto offset = Oblock->GetOffsets(State::Up, State::Right);

        ASSERT_TRUE(templateOffset == offset);

        // Right -> Down: ( 1, 0), ( 1, 0), ( 1, 0), ( 1, 0), ( 1, 0).
        templateOffset = {Position(1,0), Position(1,0), Position(1,0), Position(1,0), Position(1,0)};
        offset = Oblock->GetOffsets(State::Right, State::Down);

        ASSERT_TRUE(templateOffset == offset);

        // Down -> Left: ( 0,-1), ( 0,-1), ( 0,-1), ( 0,-1), ( 0,-1).
        templateOffset = {Position(0,-1), Position(0,-1), Position(0,-1), Position(0,-1), Position(0,-1)};
        offset = Oblock->GetOffsets(State::Down, State::Left);

        ASSERT_TRUE(templateOffset == offset);

        // Left -> Up: (-1, 0), (-1, 0), (-1, 0), (-1, 0), (-1, 0).
        templateOffset = {Position(-1,0), Position(-1,0), Position(-1,0), Position(-1,0), Position(-1,0)};
        offset = Oblock->GetOffsets(State::Left, State::Up);

        ASSERT_TRUE(templateOffset == offset);
    }

}
