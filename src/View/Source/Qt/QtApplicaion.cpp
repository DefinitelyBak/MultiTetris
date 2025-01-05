#include <View/Qt/QtApplication.h>
#include <QApplication>
#include <QtPlugin>

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)


namespace Tetris::View::Qt
{

    QtApplicaion::QtApplicaion(AbstractModelPtr model, unsigned int countWidgets)
        : _model(model), _count(countWidgets)
    {}

    void QtApplicaion::Run()
    {
        if (_count > 0)
        {
            std::string nameApllication = "Tetris";
            char* argv[1];
            argv[0] = nameApllication.data();
            int args = 1;

            // Регистрация мета-типов для использования в сигнал-слугах.
            qRegisterMetaType<MementoModelPtr>("MementoModelPtr");
            qRegisterMetaType<Model::Command>("Model::Command");

            QApplication app(args, argv);

            for (unsigned int i = 0; i < _count; ++i)
            {
                auto widget = std::make_shared<Qt::QAdapterWidget>(_model);
                _widgets.push_back(widget);
                _model->SetWidget(widget);
            }
            app.exec();
        }
        _execution = false;
    }

}