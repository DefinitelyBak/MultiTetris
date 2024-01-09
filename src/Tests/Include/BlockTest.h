#pragma once

#include <gtest/gtest.h>

#include "Precompile.h"

#include "Factory/ShapeFactory.h"


namespace Tetris::Tests
{

    using namespace Model::Blocks;
    using namespace Common::Data;

    /// @brief Сравнение описание положения фигур
    /// @param lhs Положение фигуры
    /// @param rhs Положение фигуры
    /// @return Равны или не равны
    bool IsEqual(const AbstractBlock::DescriptionFigure& lhs, const AbstractBlock::DescriptionFigure& rhs)
    {
        for(int i = 0; i < 4; ++i)
            if( lhs[i].first  != rhs[i].first || lhs[i].second != rhs[i].second)
                return false;

        return true;
    };

    /// @brief Шаблонная функция тестирования фигур
    /// @param positions Шаблонные позиции
    /// @param blockPtr Тестируемый блок
    /// @param color Ожидаемый цыет блок
    void TestTemplate(const std::vector<AbstractBlock::DescriptionFigure>& positions, std::shared_ptr<AbstractBlock> blockPtr, const Color color)
    {
        // Проверка цвета 
        ASSERT_TRUE(blockPtr->GetColor() == color);

        // Проверка начального положения
        AbstractBlock::DescriptionFigure deskField = blockPtr->GetDescription();
        bool state = blockPtr->GetState() == AbstractBlock::State::Up;
        ASSERT_TRUE(state);
        ASSERT_TRUE(IsEqual(positions[0], deskField));

        // Проверка на возможный поворот
        deskField = blockPtr->TryRotateShape();
        ASSERT_TRUE(IsEqual(positions[1], deskField));

        // Повернуть объект
        blockPtr->RotateShape();
        state = (blockPtr->GetState() == AbstractBlock::State::Right);
        ASSERT_TRUE(state);
        deskField = blockPtr->GetDescription();
        ASSERT_TRUE(IsEqual(positions[1], deskField));

        // Проверка на возможный поворот
        deskField = blockPtr->TryRotateShape();
        ASSERT_TRUE(IsEqual(positions[2], deskField));

        // Повернуть объект
        blockPtr->RotateShape();
        state = (blockPtr->GetState() == AbstractBlock::State::Down);
        ASSERT_TRUE(state);
        deskField = blockPtr->GetDescription();
        ASSERT_TRUE(IsEqual(positions[2], deskField));

        // Проверка на возможный поворот
        deskField = blockPtr->TryRotateShape();
        ASSERT_TRUE(IsEqual(positions[3], deskField));

        // Повернуть объект
        blockPtr->RotateShape();
        state = (blockPtr->GetState() == AbstractBlock::State::Left);
        ASSERT_TRUE(state);
        deskField = blockPtr->GetDescription();
        ASSERT_TRUE(IsEqual(positions[3], deskField));

        // Проверка на возможный поворот
        deskField = blockPtr->TryRotateShape();
        ASSERT_TRUE(IsEqual(positions[0], deskField));

        // Повернуть объект
        blockPtr->RotateShape();
        state = (blockPtr->GetState() == AbstractBlock::State::Up);
        ASSERT_TRUE(state);
        deskField = blockPtr->GetDescription();
        ASSERT_TRUE(IsEqual(positions[0], deskField));
    };

    /// @brief Функция инициализация положения I блока
    /// @return Положения I блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitIblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
        {
            {
	    	    AbstractBlock::PosotionFiel( 0, 2 ), // *  *  o  *  * 
	    	    AbstractBlock::PosotionFiel( 0, 1 ), // *  *  o  *  *
	    	    AbstractBlock::PosotionFiel( 0, 0 ), // *  *  0  *  *
	    	    AbstractBlock::PosotionFiel( 0,-1 )  // *  *  o  *  *
	        },     					                 // *  *  *  *  *
	        {
	    	    AbstractBlock::PosotionFiel( 2, 0 ), // *  *  *  *  *
	    	    AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *  *  *
	    	    AbstractBlock::PosotionFiel( 0, 0 ), // *  o  0  o  o
	    	    AbstractBlock::PosotionFiel(-1, 0 )  // *  *  *  *  *
	        },    					                 // *  *  *  *  *
	        {
	    	    AbstractBlock::PosotionFiel( 0, -2), // *  *  *  *  *
	    	    AbstractBlock::PosotionFiel( 0, -1), // *  *  o  *  *
	    	    AbstractBlock::PosotionFiel( 0, 0 ), // *  *  0  *  *
	    	    AbstractBlock::PosotionFiel( 0, 1 )  // *  *  o  *  *
	        }, 						                 // *  *  o  *  *
	        {				
	    	    AbstractBlock::PosotionFiel(-2, 0 ), // *  *  *  *  *
	    	    AbstractBlock::PosotionFiel(-1, 0 ), // *  *  *  *  *
	    	    AbstractBlock::PosotionFiel( 0, 0 ), // o  o  0  o  *
	    	    AbstractBlock::PosotionFiel( 1, 0 )  // *  *  *  *  *
	        }
        };
    }

    /// @brief Функция инициализация положения J блока
    /// @return Положения J блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitJblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
        {
			{
				AbstractBlock::PosotionFiel( 0, 1 ), // *  o  *
				AbstractBlock::PosotionFiel( 0, 0 ), // *  0  *
				AbstractBlock::PosotionFiel( 0,-1 ), // o  o  *
				AbstractBlock::PosotionFiel(-1,-1 )
			},
			{
				AbstractBlock::PosotionFiel( 1, 0 ), // o  *  *
				AbstractBlock::PosotionFiel( 0, 0 ), // o  0  o
				AbstractBlock::PosotionFiel(-1, 0 ), // *  *  *
				AbstractBlock::PosotionFiel(-1, 1 )
			},
			{
				AbstractBlock::PosotionFiel( 0,-1 ), // *  o  o
				AbstractBlock::PosotionFiel( 0, 0 ), // *  0  *
				AbstractBlock::PosotionFiel( 0, 1 ), // *  o  *
				AbstractBlock::PosotionFiel( 1, 1 )
			},
			{
				AbstractBlock::PosotionFiel(-1, 0 ), // *  *  *
				AbstractBlock::PosotionFiel( 0, 0 ), // o  0  o
				AbstractBlock::PosotionFiel( 1, 0 ), // *  *  o
				AbstractBlock::PosotionFiel( 1,-1 )
			}
        };
    }

    /// @brief Функция инициализация положения L блока
    /// @return Положения L блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitLblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
        {
			{
				AbstractBlock::PosotionFiel( 0, 1 ), // *  o  *
				AbstractBlock::PosotionFiel( 0, 0 ), // *  0  *
				AbstractBlock::PosotionFiel( 0,-1 ), // *  o  o
				AbstractBlock::PosotionFiel( 1,-1 )
			},
			{
				AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *
				AbstractBlock::PosotionFiel( 0, 0 ), // o  0  o
				AbstractBlock::PosotionFiel(-1, 0 ), // o  *  *
				AbstractBlock::PosotionFiel(-1,-1 )
			},
			{
				AbstractBlock::PosotionFiel( 0,-1 ), // o  o  *
				AbstractBlock::PosotionFiel( 0, 0 ), // *  0  *
				AbstractBlock::PosotionFiel( 0, 1 ), // *  o  *
				AbstractBlock::PosotionFiel(-1, 1 )
			},
			{
				AbstractBlock::PosotionFiel(-1, 0 ), // *  *  o
				AbstractBlock::PosotionFiel( 0, 0 ), // o  0  o
				AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *
				AbstractBlock::PosotionFiel( 1, 1 )
			}
		};
    }

    /// @brief Функция инициализация положения O блока
    /// @return Положения O блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitOblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
		{
            {
			    AbstractBlock::PosotionFiel( 0, 1 ), // o  o  * 
			    AbstractBlock::PosotionFiel( 0, 0 ), // o  0  *
			    AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *
			    AbstractBlock::PosotionFiel( 1, 1 )
			},
			{
			    AbstractBlock::PosotionFiel( 0, 1 ), // o  o  *  
			    AbstractBlock::PosotionFiel( 0, 0 ), // o  0  *  
			    AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *  
			    AbstractBlock::PosotionFiel( 1, 1 )
			},
			{
			    AbstractBlock::PosotionFiel( 0, 1 ), // o  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ), // o  0  *
			    AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *
			    AbstractBlock::PosotionFiel( 1, 1 )
			},
			{
			    AbstractBlock::PosotionFiel( 0, 1 ), // o  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ), // o  0  *
			    AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *
			    AbstractBlock::PosotionFiel( 1, 1 )
			}
		};
    }

    /// @brief Функция инициализация положения S блока
    /// @return Положения S блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitSblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
		{
			{
			    AbstractBlock::PosotionFiel( 1, 0 ), // *  *  *  *
			    AbstractBlock::PosotionFiel( 0, 0 ), // *  0  o  *
			    AbstractBlock::PosotionFiel( 0,-1 ), // o  o  *  *
			    AbstractBlock::PosotionFiel(-1,-1 )  // *  *  *  *
			},
			{
				AbstractBlock::PosotionFiel( 0,-1 ), // o  *  *  *
				AbstractBlock::PosotionFiel( 0, 0 ), // o  0  *  *
				AbstractBlock::PosotionFiel(-1, 0 ), // *  o  *  *
				AbstractBlock::PosotionFiel(-1, 1 )  // *  *  *  *
			},
			{
				AbstractBlock::PosotionFiel(-1, 0 ), // *  o  o  *
				AbstractBlock::PosotionFiel( 0, 0 ), // o  0  *  *
				AbstractBlock::PosotionFiel( 0, 1 ), // *  *  *  *
				AbstractBlock::PosotionFiel( 1, 1 )  // *  *  *  *
			},
			{
				AbstractBlock::PosotionFiel( 0, 1 ), // *  o  *  *
				AbstractBlock::PosotionFiel( 0, 0 ), // *  0  o  *
				AbstractBlock::PosotionFiel( 1, 0 ), // *  *  o  *
				AbstractBlock::PosotionFiel( 1,-1 )  // *  *  *  *
			}
		};
    };

    /// @brief Функция инициализация положения T блока
    /// @return Положения T блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitTblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
		{
			{
			    AbstractBlock::PosotionFiel( 1, 0 ),  // *  *  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // o  0  o
			    AbstractBlock::PosotionFiel( 0,-1 ),  // *  o  *
			    AbstractBlock::PosotionFiel(-1, 0 )   
			},
			{
			    AbstractBlock::PosotionFiel( 0,-1 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // o  0  *
			    AbstractBlock::PosotionFiel(-1, 0 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 0, 1 ) 
			},
			{
			    AbstractBlock::PosotionFiel(-1, 0 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // o  0  o
			    AbstractBlock::PosotionFiel( 0, 1 ),  // *  *  *
			    AbstractBlock::PosotionFiel( 1, 0 ) 
			},
			{
			    AbstractBlock::PosotionFiel( 0, 1 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // *  0  o
			    AbstractBlock::PosotionFiel( 1, 0 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 0,-1 )   
			}  
		};
    };

    /// @brief Функция инициализация положения Z блока
    /// @return Положения Z блока Up, Right, Down, Left
    std::vector<AbstractBlock::DescriptionFigure> InitZblock()
    {
        return std::vector<AbstractBlock::DescriptionFigure>
		{
			{
			    AbstractBlock::PosotionFiel(-1, 0 ),  // *  *  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // o  0  *
			    AbstractBlock::PosotionFiel( 0,-1 ),  // *  o  o
			    AbstractBlock::PosotionFiel( 1,-1 )   // *  *  *
			},
			{
			    AbstractBlock::PosotionFiel( 0, 1 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // o  0  *
			    AbstractBlock::PosotionFiel(-1, 0 ),  // o  *  *
			    AbstractBlock::PosotionFiel(-1,-1 )   // *  *  *
			},
			{
			    AbstractBlock::PosotionFiel( 1, 0 ),  // o  o  *
			    AbstractBlock::PosotionFiel( 0, 0 ),  // *  0  o
			    AbstractBlock::PosotionFiel( 0, 1 ),  // *  *  *
			    AbstractBlock::PosotionFiel(-1, 1 )   // *  *  *
			},
			{
			    AbstractBlock::PosotionFiel( 0,-1 ),  // *  *  o
			    AbstractBlock::PosotionFiel( 0, 0 ),  // *  0  o
			    AbstractBlock::PosotionFiel( 1, 0 ),  // *  o  *
			    AbstractBlock::PosotionFiel( 1, 1 )   // *  *  *
			}  
		};
    };

} // namespace