#include "Qt/Widget.h"
#include <Qt>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>
#include <iostream>

#include "Qt/KeyPressFilter.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Qt/PreviewBlock.h"
//#include <QQuickView>


namespace Tetris::View::Qt
{
    
    Widget::Widget(QWidget* parent): QWidget(parent), _map(new Map(nullptr, true)), _preview(new PreviewBlock(nullptr,true))
    {
        setFocusPolicy(::Qt::ClickFocus);

        QWidget *container = QWidget::createWindowContainer(_map, this);
        KeyPressFilter* filter = new KeyPressFilter(this);
        container->setMinimumSize(420,800);
        container->setFocusPolicy(::Qt::ClickFocus);
        _map->installEventFilter(filter);
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(container);

        QWidget *containerPrev = QWidget::createWindowContainer(_preview, this);
        containerPrev->setMinimumSize(180, 150);
        containerPrev->setMaximumSize(180, 150);
        containerPrev->setFocusPolicy(::Qt::NoFocus);
        QVBoxLayout* hLayout = new QVBoxLayout;
        hLayout->addWidget(containerPrev);
        _text = new QLabel(this);
        _text->setMinimumSize(180, 100);
        _text->setMaximumSize(180, 100);
        _text->setTextFormat(::Qt::PlainText);
        QFont font;
        font.setFamily("Arial"); // Семейство шрифта
        font.setPointSize(24); // Размер шрифта
        font.setBold(true); // Жирный шрифт

        _text->setFont(font);

            // Установка выравнивания текста
        _text->setAlignment(::Qt::AlignCenter); // Горизонтальное выравнивание по центру
        _text->setAlignment(::Qt::AlignVCenter); // Вертикальное выравнивание по центру

        hLayout->addWidget(_text);
        auto temp = new QWidget(this);
        temp->setMaximumWidth(180);
        hLayout->addWidget(temp);

        layout->addLayout(hLayout);

        setLayout(layout);

        _text->setText(QString("Score:\n0"));
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
