#include <gtest/gtest.h>

#include "Precompile.h"

#include "Map.h"
#include "Factory/BlocksFactory.h"



namespace Tetris::Test
{
    using Model::TypeColor::None;
    using Model::TypeColor::Green;

    bool operator==(const Model::DataMap& lhs, const Model::DataMap& rhs)
    {
        if(lhs.size() != rhs.size())
            return false;

        for (int i = 0; i < lhs.size(); ++i)
            if(lhs[i] != rhs[i])
                return false;

        return true;
    };

    class MapTest : public ::testing::Test
    {
    protected:
        MapTest()
        {
            factorGreen.add<Model::Tblock>(Model::IdShape::Tblock);
        };

        Model::BlocksFactory factorGreen;
    };

    TEST(MapTests, EmptGreenMap)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None }; // 25 строка

        Model::Map map(10,24);
        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlock)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, Green, Green, Green, None, None, None, None,
                                 None, None, None, None, Green, None, None, None, None, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockOneStepDown)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, Green, Green, Green, None, None, None, None,
                                 None, None, None, None, Green, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));
        map.MoveBlock(Model::Command::Down);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockOneStepLeft)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, Green, Green, Green, None, None, None, None, None,
                                 None, None, None, Green, None, None, None, None, None, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));
        map.MoveBlock(Model::Command::Left);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockOneStepRight)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, Green, Green, Green, None, None, None,
                                 None, None, None, None, None, Green, None, None, None, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));
        map.MoveBlock(Model::Command::Right);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockFiveStepsRight)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, Green, Green, Green,
                                 None, None, None, None, None, None, None, None, Green, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));
        for(int i = 0; i < 5; ++i)
            map.MoveBlock(Model::Command::Right);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlockFiveStepsLeft)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, None, None, None, None, None, None, None, // 1 строка
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 Green, Green, Green, None, None, None, None, None, None, None,
                                 None, Green, None, None, None, None, None, None, None, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));
        for(int i = 0; i < 5; ++i)
            map.MoveBlock(Model::Command::Left);

        ASSERT_EQ(mocMap, map.GetMap());
    }

    TEST_F(MapTest, MapWithTBlock25StepsDown)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {None, None, None, Green, Green, Green, None, None, None, None, // 1 строка
                                 None, None, None, None, Green, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None,
                                 None, None, None, None, None, None, None, None, None, None }; // 25 строка
        Model::Map map(10,24);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factorGreen.Create(Model::IdShape::Tblock, Green)));
        for(int i = 0; i < 25; ++i)
            map.MoveBlock(Model::Command::Down);

        ASSERT_EQ(mocMap, map.GetMap());
    }

}
