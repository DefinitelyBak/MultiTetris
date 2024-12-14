#include "Precompile.h"

#include "Forwards.h"
#include "AbstractModel.h"
#include <Qt/Widget.h>


namespace Tetris::View
{
    
    class QtApplicaion
    {
    public:
        QtApplicaion(AbstractModelPtr model, unsigned int countWidgets);
        ~QtApplicaion();

        void Run();

        bool isExecution() const; 

    private:
        unsigned int _count;

        std::list<AbstractWidgetPtr> _widgets;
        AbstractModelPtr _model;

        std::thread _thread;
        std::atomic<bool> _execution;
    };

} // namespace