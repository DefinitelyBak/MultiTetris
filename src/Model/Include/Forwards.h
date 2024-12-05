#pragma once

#include <memory>


namespace Tetris
{
    namespace Model
    {
        class AbstractWidget;

        namespace Blocks
        {
            class AbstractBlock;
        }    
    }

    typedef std::shared_ptr<Model::Blocks::AbstractBlock> AbstractBlockPtr;
    typedef std::shared_ptr<Model::AbstractWidget> AbstractWidgetPtr;
}
