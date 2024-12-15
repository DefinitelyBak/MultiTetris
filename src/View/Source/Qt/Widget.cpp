#include "Qt/Widget.h"
#include <Qt>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>
#include <iostream>

#include <QVBoxLayout>

//#include <QQuickView>


namespace Tetris::View::Qt
{
    
    Widget::Widget(QWidget* parent): QWidget(parent), _map(new Map(nullptr, true))
    {
        setFocusPolicy(::Qt::ClickFocus);

        QWidget *container = QWidget::createWindowContainer(_map, this);
        container->setMinimumSize(600,800);
        //container->setMaximumSize(...);
        container->setFocusPolicy(::Qt::ClickFocus);
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(container);
        setLayout(layout);
    };

    //
    void Widget::keyPressEvent(QKeyEvent *event)
    {
        switch (event->key())
        {
        case ::Qt::Key_A:
        case ::Qt::Key_Left:
            //_modelEvents.push(Model::Command::Left);
            emit SignalUpdateModel(Model::Command::Left);
            return;
        case ::Qt::Key_W:
        case ::Qt::Key_Up:
            //_modelEvents.push(Model::Command::RotateRight);
            emit SignalUpdateModel(Model::Command::RotateRight);
            return;
        case ::Qt::Key_D:
        case ::Qt::Key_Right:
            //_modelEvents.push(Model::Command::Right);
            emit SignalUpdateModel(Model::Command::Right);
            return;
        case ::Qt::Key_S:
        case ::Qt::Key_Down:
            //_modelEvents.push(Model::Command::Down);
            emit SignalUpdateModel(Model::Command::Down);
            return;
        default:
            QWidget::keyPressEvent(event);
            return;
        }
    }
       
}
