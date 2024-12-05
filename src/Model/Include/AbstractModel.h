#pragma once

#include "Forwards.h"
#include "Types.h"

#include "AbstractWidget.h"


namespace Tetris::Model
{
    class AbstractModel
    {
    public:

        virtual ~AbstractModel() = default;

        virtual void SlotUpdate(Command command) = 0;

        virtual void SetView(AbstractWidgetPtr view) = 0;
    };

}