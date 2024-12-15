#pragma once

#include "Qt/Widget.h"
#include <Qt>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>
#include "Qt/KeyPressFilter.h"
#include "Qt/Widget.h"
#include <QDebug>
#include <QObject>

#include "Qt/Widget.h"
#include <QWidget>


namespace Tetris::View::Qt
{

    class Adapter: public QObject
    {
        Q_OBJECT
    public:
        Adapter(AbstractModelPtr model);

        void SetWidget();

        void Close();

        void UpdateView(Model::DescriptionModel desc);

    signals:
        void signalUpdateWidget(Model::DescriptionModel desc);
        void signalCloseWidget();
        void signalUpdateView();

    public slots:

        void EmitUpdateSignal(Model::DescriptionModel);
        
        void SlotUpdateModel(Model::Command cmd);

    private:
        Controller::MoveController _controller;

        int abs;
    };

}