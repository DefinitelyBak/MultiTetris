#include "Qt/Widget.h"
#include <Qt>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>
#include <iostream>


namespace Tetris::View::Qt
{
    
    Widget::Widget(AbstractModelPtr model): AbstractWidget(), QWidget(nullptr), _controller(model)
    {};

    bool Widget::IsOpen() const
    {
        return _windowOpen;
    }

/// Обарботчик событий Qt по факту надо сбытия Qt переводить в AbstractWidget
    bool Widget::event(QEvent* event)
    {
        if (event->type() == QEvent::Type::Paint ||
            event->type() == QEvent::Type::Resize ||
            event->type() == QEvent::Type::Show)
            {
                _qtEvent = event;
                Update();
                return true;
            }
        
        return QWidget::event(event);
    }

    //
    void Widget::keyPressEvent(QKeyEvent *event)
    {
        switch (event->key())
        {
        case ::Qt::Key_A:
        case ::Qt::Key_Left:
            _modelEvents.push(Model::Command::Left);
            return;
        case ::Qt::Key_W:
        case ::Qt::Key_Up:
            _modelEvents.push(Model::Command::RotateRight);
            return;
        case ::Qt::Key_D:
        case ::Qt::Key_Right:
            _modelEvents.push(Model::Command::Right);
            return;
        case ::Qt::Key_S:
        case ::Qt::Key_Down:
            _modelEvents.push(Model::Command::Down);
            return;
        default:
            QWidget::keyPressEvent(event);
            return;
        }
    }

    void Widget::UpdateWidget()
    {
        if(!_qtEvent)
        {
            QWidget::event(_qtEvent);
            _qtEvent = nullptr;
        }
    }
        
// Тут должны быть события для модели.
    void Widget::ProcessingEvents()
    {
        if (! _modelEvents.empty())
        {
            auto cmd =  _modelEvents.top();
            _modelEvents.pop();
            _controller.Move(cmd);
        }
    }

    // Обновление карты
    void Widget::UpdateView(Model::DescriptionModel descriptionModel)
    {}

    /// Событие закрытие окна из модели 
    void Widget::CloseEvent()
    {
        _windowOpen = false;
        close();
    }

}
