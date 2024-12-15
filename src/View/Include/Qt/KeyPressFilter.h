#pragma once

#include <QApplication>
#include <QWidget>
#include <QWindow>
#include <QKeyEvent>


class KeyPressFilter : public QObject
{
    Q_OBJECT
public:
    explicit KeyPressFilter(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qApp->sendEvent(parent(), keyEvent); // Перенаправляем событие родителю
            return true; // Событие обработано
        }
        return QObject::eventFilter(obj, event);
    }
};