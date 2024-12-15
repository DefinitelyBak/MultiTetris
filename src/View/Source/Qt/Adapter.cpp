#include "Qt/Adapter.h"


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

        Adapter::Adapter(AbstractModelPtr model):QObject(nullptr), _controller(model)
        {
            abs = 11111111;
        }

        void Adapter::SetWidget()
        {
            Widget* widget = new Widget();
            connect(this, &Adapter::signalCloseWidget, widget, &Widget::close);
            connect(this, &Adapter::signalUpdateWidget, widget, &Widget::SlotUpdateView);
            connect(this, &Adapter::signalUpdateWidget, this, &Adapter::EmitUpdateSignal);
            connect(widget, &Widget::SignalUpdateModel, this, &Adapter::SlotUpdateModel);
            widget->show();
        }

        void Adapter::Close()
        {
            emit signalCloseWidget();
        }

        void Adapter::UpdateView(Model::DescriptionModel desc)
        {
            emit signalUpdateWidget(desc);
        }


        void Adapter::EmitUpdateSignal(Model::DescriptionModel)
        {
            emit signalUpdateView();
        };
        
        void Adapter::SlotUpdateModel(Model::Command cmd)
        {
            _controller.Move(cmd);
        }

}