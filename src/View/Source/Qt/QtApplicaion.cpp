#include "Qt/QtApplication.h"
#include <QApplication>
#include "Qt/QAdapterWidget.h"


namespace Tetris::View::Qt
{

    QtApplicaion::QtApplicaion(AbstractModelPtr model, unsigned int countWidgets)
        : _model(model), _count(countWidgets), _execution(true)
    {
        _thread = std::thread(&QtApplicaion::Run, this);
    }

    QtApplicaion::~QtApplicaion()
    {
        if (_thread.joinable())
            _thread.join();
    }

    void QtApplicaion::Run()
    {
        char* argv[] = {"Tetris"};
        int args = 1;

        // Регистрация мета-типов для использования в сигнал-слугах.
        qRegisterMetaType<DescriptionModelPtr>("DescriptionModelPtr");
        qRegisterMetaType<Model::Command>("Model::Command");

        QApplication app(args, argv);
        auto adapter = std::make_shared<Qt::QAdapterWidget>(_model);

        for (unsigned int i = 0; i < _count; ++i)
        {
            adapter->CreateWidget();
        }

        _model->SetWidget(adapter);
        app.exec();
        _execution = false;
    }


    bool QtApplicaion::isExecution() const
    {
        return _execution;
    }
}