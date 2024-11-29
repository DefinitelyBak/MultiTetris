#pragma once


#include "Types.h"

namespace Tetris::View
{
    using namespace Model;

    class AbstractWidget
    {
    public:
    
        ~AbstractWidget() = default;

        virtual void Update() = 0;

        //virtual void SlotUpdateView(DataMap map, MapSize size, unsigned int score) = 0;

        virtual bool IsOpen() const = 0;
    };
}