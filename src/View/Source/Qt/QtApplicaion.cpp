#include "Qt/QtApplication.h"

#include <QApplication>

namespace Tetris::View
{

        QtApplicaion::QtApplicaion(AbstractModelPtr model, unsigned int countWidgets): _model(model), _count(countWidgets)
        {
            _execution = true;
            _thread = std::thread(Tetris::View::QtApplicaion::Run, this);
        }

        QtApplicaion::~QtApplicaion()
        {
            _thread.join();
        }

        void QtApplicaion::Run()
        {
            char* argv[] = {"Tetris"};
            int args = 1;
            QApplication app(args, argv);

            for(int i = 0; i < _count; ++i)
            {
                Qt::Widget* wptr = new Qt::Widget(_model);
                AbstractWidgetPtr w(wptr);
                _widgets.push_back(w);
                _model->SetView(w);
                wptr->show();
            }

            app.exec();
            _execution = false;
        }

        bool QtApplicaion::isExecution() const
        {
            return _execution;
        }
}