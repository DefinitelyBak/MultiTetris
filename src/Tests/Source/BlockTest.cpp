#include "BlockTest.h"


namespace Tetris::Tests
{

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

        Model::Blocks::ShapeFactory _factory;
    };

    TEST_F(BlockTest, Iblock)
    {
        auto positions = InitIblock();
        std::shared_ptr<AbstractBlock> Iblock(_factory.Create(IdShape::Iblock, Color::Green));

        TestTemplate(positions, Iblock, Color::Green);
    }

    TEST_F(BlockTest, Jblock)
    {
        auto positions = InitJblock();
        std::shared_ptr<AbstractBlock> Jblock(_factory.Create(IdShape::Jblock, Color::Green));

        TestTemplate(positions, Jblock, Color::Green);
    }

    TEST_F(BlockTest, Lblock)
    {
        auto positions = InitJblock();
        std::shared_ptr<AbstractBlock> Jblock(_factory.Create(IdShape::Jblock, Color::Green));

        TestTemplate(positions, Jblock, Color::Green);
    }

    TEST_F(BlockTest, Oblock)
    {
        auto positions = InitOblock();
        std::shared_ptr<AbstractBlock> Oblock(_factory.Create(IdShape::Oblock, Color::Green));

        TestTemplate(positions, Oblock, Color::Green);
    }

    TEST_F(BlockTest, Sblock)
    {
        auto positions = InitSblock();
        std::shared_ptr<AbstractBlock> Sblock(_factory.Create(IdShape::Sblock, Color::Green));

        TestTemplate(positions, Sblock, Color::Green);
    }

    TEST_F(BlockTest, Tblock)
    {
        auto positions = InitTblock();
        std::shared_ptr<AbstractBlock> Tblock(_factory.Create(IdShape::Tblock, Color::Green));

        TestTemplate(positions, Tblock, Color::Green);
    }

    TEST_F(BlockTest, Zblock)
    {
        auto positions = InitZblock();
        std::shared_ptr<AbstractBlock> Zblock(_factory.Create(IdShape::Zblock, Color::Green));

        TestTemplate(positions, Zblock, Color::Green);
    }
}