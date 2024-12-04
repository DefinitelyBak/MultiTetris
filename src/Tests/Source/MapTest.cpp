#include <gtest/gtest.h>

#include "Precompile.h"

#include "Map.h"
#include "Factory/ShapeFactory.h"

#define X Model::TypeColor::None
#define Y Model::TypeColor::Green
#define Z Model::TypeColor::Red


namespace Tetris::Test
{

    bool operator==(const Model::DataMap& lhs, const Model::DataMap& rhs)
    {
        if(lhs.size() != rhs.size())
            return false;

        for (int i = 0; i < lhs.size(); ++i)
            if(lhs[i] != rhs[i])
                return false;

        return true;
    };

    TEST(MapTests, EmptyMap)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X }; // 25 строка

        Model::Map map;
        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlock)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, Y, Y, Y, X, X, X, X,
                                 X, X, X, X, Y, X, X, X, X, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));

        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlockOneStepDown)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, Y, Y, Y, X, X, X, X,
                                 X, X, X, X, Y, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));
        map.MoveBlock(Model::Command::Down);

        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlockOneStepLeft)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, Y, Y, Y, X, X, X, X, X,
                                 X, X, X, Y, X, X, X, X, X, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));
        map.MoveBlock(Model::Command::Left);

        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlockOneStepRight)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, Y, Y, Y, X, X, X,
                                 X, X, X, X, X, Y, X, X, X, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));
        map.MoveBlock(Model::Command::Right);

        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlockFiveStepsRight)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, Y, Y, Y,
                                 X, X, X, X, X, X, X, X, Y, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));
        for(int i = 0; i < 5; ++i)
            map.MoveBlock(Model::Command::Right);

        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlockFiveStepsLeft)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, X, X, X, X, X, X, X, // 1 строка
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 Y, Y, Y, X, X, X, X, X, X, X,
                                 X, Y, X, X, X, X, X, X, X, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));
        for(int i = 0; i < 5; ++i)
            map.MoveBlock(Model::Command::Left);

        EXPECT_EQ(mocMap, map.GetMap());
    }

    TEST(MapTests, MapWithTBlock25StepsDown)
    {
        /// Здесь будет moc карты
        Model::DataMap mocMap = {X, X, X, Y, Y, Y, X, X, X, X, // 1 строка
                                 X, X, X, X, Y, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X,
                                 X, X, X, X, X, X, X, X, X, X }; // 25 строка
        Model::Map map;

        Model::BlocksFactory factory;
        factory.add<Model::Tblock>(Model::IdShape::Tblock);
        map.SetBlock(std::shared_ptr<Model::AbstractBlock>(factory.Create(Model::IdShape::Tblock, Y)));
        for(int i = 0; i < 25; ++i)
            map.MoveBlock(Model::Command::Down);

        EXPECT_EQ(mocMap, map.GetMap());
    }

}
