#include "Qt/QtApplication.h"

#include <QApplication>

namespace Tetris::View
{

        QtApplicaion::QtApplicaion(AbstractModelPtr model, unsigned int countWidgets, int argc, char *argv[]): _model(model), _count(countWidgets)
        {
            _argc = argc;
            _argv = argv;
            _execution = true;
            _thread = std::thread(Tetris::View::QtApplicaion::Run, this);
        }

        QtApplicaion::~QtApplicaion()
        {
            _thread.join();
        }

        void QtApplicaion::Run()
        {
            int argc;
            char* argv;
            QApplication app(_argc, _argv);

            QWidget widget;
            widget.show();

            app.exec();
            _execution = false;
        }

        bool QtApplicaion::isExecution() const
        {
            return _execution;
        }
}