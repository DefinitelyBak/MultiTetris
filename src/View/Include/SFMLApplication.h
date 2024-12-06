#include "Precompile.h"

#include "AbstractModel.h"


namespace Tetris::View
{
    class SFMLApplication
    {
    public:
        SFMLApplication(std::shared_ptr<Model::AbstractModel> model, unsigned int countWidgets);

        void Run();

    private:

        std::string _pathFont;

        unsigned int _count;

        std::list<AbstractWidgetPtr> _widgets;

        std::shared_ptr<Model::AbstractModel> _model;
    };

}