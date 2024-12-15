#include "Qt/QtApplication.h"
#include <QApplication>
#include "Qt/QAdapterWidget.h"


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

            qRegisterMetaType<Model::DescriptionModel>("Model::DescriptionModel");
            qRegisterMetaType<Model::Command>("Model::Command");

            QApplication app(args, argv);
            std::shared_ptr<Qt::QAdapterWidget> adapter = std::make_shared<Qt::QAdapterWidget>(_model);
            AbstractWidgetPtr ptr = adapter;
            
            for(int i = 0; i < _count; ++i)
            {
                adapter->SetWidget();
            }
            
            _model->SetView(ptr);
            app.exec();
            _execution = false;
        }

        bool QtApplicaion::isExecution() const
        {
            return _execution;
        }
}