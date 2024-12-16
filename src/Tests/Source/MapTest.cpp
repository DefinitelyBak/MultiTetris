#include <gtest/gtest.h>

#include "Precompile.h"

#include "Map.h"
#include "Factory/BlocksFactory.h"
#include "blocks/Iblock.h"
#include "blocks/Jblock.h"
#include "blocks/Lblock.h"
#include "blocks/Oblock.h"
#include "blocks/Sblock.h"
#include "blocks/Tblock.h"
#include "blocks/Zblock.h"


namespace Tetris::Test
{
    using Model::TypeColor;
    using Model::TypeColor::None;
    using Model::TypeColor::Green;

    bool operator==(const std::vector<TypeColor>& lhs, const std::vector<TypeColor>& rhs)
    {
        if(lhs.size() != rhs.size())
            return false;

        for (size_t i = 0; i < lhs.size(); ++i)
            if(lhs[i] != rhs[i])
                return false;

        return true;
    }

    class MapTest : public ::testing::Test
    {
    protected:
        MapTest()
        {
            factorGreen.add<Model::Blocks::Tblock>(Model::TypeBlock::Tblock);
        }

        Model::Blocks::BlocksFactory factorGreen;
    };

    TEST(MapTests, EmptGreenMap)
    {
        std::vector<TypeColor> mocMap(240, None); // 10 columns x 24 rows
        Model::Map map(10, 24);
        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlock)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[22] = mocMap[23] = mocMap[24] = Green; // T-block position

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockOneStepDown)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[32] = mocMap[33] = mocMap[34] = Green; // T-block position after moving down

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));
        map.MoveBlock(Model::Command::Down);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockOneStepLeft)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[21] = mocMap[22] = mocMap[23] = Green; // T-block position after moving left

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));
        map.MoveBlock(Model::Command::Left);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockOneStepRight)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[23] = mocMap[24] = mocMap[25] = Green; // T-block position after moving right

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));
        map.MoveBlock(Model::Command::Right);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockFiveStepsRight)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[25] = mocMap[26] = mocMap[27] = Green; // T-block position after moving right 5 times

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));
        for(int i = 0; i < 5; ++i)
            map.MoveBlock(Model::Command::Right);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockFiveStepsLeft)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[21] = mocMap[22] = mocMap[23] = Green; // T-block position after moving left 5 times

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));
        for(int i = 0; i < 5; ++i)
            map.MoveBlock(Model::Command::Left);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlock25StepsDown)
    {
        std::vector<TypeColor> mocMap(240, None);
        mocMap[200] = mocMap[201] = mocMap[202] = Green; // T-block position after moving down 25 times

        Model::Map map(10, 24);
        map.SetBlock(AbstractBlockPtr(factorGreen.Create(Model::TypeBlock::Tblock, Green)));
        for(int i = 0; i < 25; ++i)
            map.MoveBlock(Model::Command::Down);

        ASSERT_EQ(mocMap, map.GetMap());
    }
}