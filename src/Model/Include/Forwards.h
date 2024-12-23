#pragma once

#include "Precompile.h"


namespace Tetris
{
    namespace Model
    {
        class AbstractModel;
        class AbstractWidget;
        class DescriptionModel;

        namespace Blocks
        {
            class AbstractBlock;
        }    
    }

    typedef std::shared_ptr<Model::DescriptionModel> DescriptionModelPtr;
    typedef std::shared_ptr<Model::Blocks::AbstractBlock> AbstractBlockPtr;
    typedef std::shared_ptr<Model::AbstractWidget> AbstractWidgetPtr;
    typedef std::shared_ptr<Model::AbstractModel> AbstractModelPtr;
} // namespace Tetris
