#pragma once

#include "Types.h"

namespace Tetris::View
{
    using namespace Model;

    class AbstractWidget
    {
    public:
        virtual ~AbstractWidget() = default;

        virtual void Update() = 0;

        virtual void SlotUpdateView(Model::DescriptionMap) = 0;

        virtual bool IsOpen() const = 0;
    };
}