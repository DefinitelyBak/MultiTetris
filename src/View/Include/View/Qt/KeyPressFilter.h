#pragma once

#include <View/Precompile.h>
#include <View/Export.h>


namespace Tetris::View::Qt
{
    /// @brief Класс для фильтрации событий нажатия клавиш.
    /// Наследуется от QObject и переопределяет метод eventFilter для обработки событий клавиатуры.
    class VIEW_EXPORT KeyPressFilter final: public QObject
    {
        Q_OBJECT 

    public:
        
        /// @brief Конструктор класса.
        /// Инициализирует объект фильтра клавиш.
        /// @param parent Указатель на родительский объект, по умолчанию nullptr.
        explicit KeyPressFilter(QObject *parent = nullptr) : QObject(parent) {}

    public slots:
        /// @brief Метод для фильтрации событий.
        /// Обрабатывает события нажатия клавиш и перенаправляет их родительскому объекту.
        /// @param obj Указатель на объект, которому принадлежит событие.
        /// @param event Указатель на событие, которое нужно обработать.
        /// @return true, если событие обработано; false в противном случае.
        bool eventFilter(QObject *obj, QEvent *event) override
        {
            if (event->type() == QEvent::KeyPress) {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                qApp->sendEvent(parent(), keyEvent); 
                return true;
            }
            return QObject::eventFilter(obj, event);
        }
    };

} // namespace Tetris::View::Qt
