#pragma once

#include <memory>


namespace Tetris
{
    namespace Model
    {
        class AbstractModel;
        class AbstractWidget;
        class MementoModel;

        namespace Blocks
        {
            class AbstractBlock;
        }    
    }

    typedef std::shared_ptr<Model::MementoModel> MementoModelPtr;
    typedef std::shared_ptr<Model::Blocks::AbstractBlock> AbstractBlockPtr;
    typedef std::shared_ptr<Model::AbstractWidget> AbstractWidgetPtr;
    typedef std::shared_ptr<Model::AbstractModel> AbstractModelPtr;
} // namespace Tetris
