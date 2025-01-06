#pragma once

#include <memory>


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
        class AbstractApplication;

        namespace SFML
        {
            class Widget;   
        }

        typedef std::shared_ptr<AbstractApplication> AbstractApplicationPtr;
        typedef std::shared_ptr<Model::Blocks::AbstractBlock> AbstractBlockPtr;
        typedef std::shared_ptr<Model::AbstractWidget> AbstractWidgetPtr;
        typedef std::shared_ptr<Model::AbstractModel> AbstractModelPtr;

        typedef std::shared_ptr<SFML::Widget> SFMLWidgetPtr;
    }

} // namespace Tetris
