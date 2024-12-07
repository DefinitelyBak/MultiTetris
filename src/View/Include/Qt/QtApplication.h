#include "Precompile.h"

#include "Forwards.h"
#include "AbstractModel.h"
#include <QWidget>

namespace Tetris::View
{
    
    class QtApplicaion
    {
    public:
        QtApplicaion(AbstractModelPtr model, unsigned int countWidgets, int argc, char *argv[]);
        ~QtApplicaion();

        void Run();

        bool isExecution() const; 

    private:
        unsigned int _count;

        std::list<QWidget> _widgets;
        AbstractModelPtr _model;
        int _argc;
        char** _argv;

        std::thread _thread;
        std::atomic<bool> _execution;
    };

} // namespace