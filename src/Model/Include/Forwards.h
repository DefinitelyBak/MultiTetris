#pragma once

#include "Precompile.h"


namespace Tetris
{
    namespace Model
    {
        class AbtractModel;
        class AbstractWidget;

        namespace Blocks
        {
            class AbstractBlock;
        }    
    }

    typedef std::shared_ptr<Model::Blocks::AbstractBlock> AbstractBlockPtr;
    typedef std::shared_ptr<Model::AbstractWidget> AbstractWidgetPtr;
    typedef std::shared_ptr<Model::AbtractModel> AbtractModelPtr;
}
