#include "Precompile.h"

#include "Forwards.h"
#include "AbstractModel.h"


namespace Tetris::View
{
    
    class SFMLApplication
    {
    public:
        SFMLApplication(AbstractModelPtr model, unsigned int countWidgets);
        ~SFMLApplication();

        void Run();

        bool isExecution() const; 

    private:
        std::string _pathFont;
        unsigned int _count;

        std::list<AbstractWidgetPtr> _widgets;
        AbstractModelPtr _model;

        std::thread _thread;
        bool _execution;
    };

} // namespace