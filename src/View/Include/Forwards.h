#pragma once

#include "Precompile.h"


namespace Tetris
{
    namespace Model
    {
        class AbstractModel;
        class AbstractWidget;

        namespace Blocks
        {
            class AbstractBlock;
        }    
    }
    
    namespace View
    {
        class IApplication;

        typedef std::shared_ptr<IApplication> AbstractApplicationPtr;
        typedef std::shared_ptr<Model::Blocks::AbstractBlock> AbstractBlockPtr;
        typedef std::shared_ptr<Model::AbstractWidget> AbstractWidgetPtr;
        typedef std::shared_ptr<Model::AbstractModel> AbstractModelPtr;
    }

} // namespace Tetris
