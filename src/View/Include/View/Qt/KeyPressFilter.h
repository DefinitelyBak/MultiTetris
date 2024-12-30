#pragma once

#include <View/Export.h>
#include <View/Precompile.h>


namespace Tetris::View::Qt
{
    /**
     * @class KeyPressFilter
     * @brief Класс для фильтрации событий нажатия клавиш.
     * Наследуется от QObject и переопределяет метод eventFilter для обработки событий клавиатуры.
     */
    class VIEW_EXPORT KeyPressFilter : public QObject
    {
        Q_OBJECT // Макрос, необходимый для использования сигналов и слотов в Qt

    public:
        /**
         * @brief Конструктор класса.
         * Инициализирует объект фильтра клавиш.
         * @param parent Указатель на родительский объект, по умолчанию nullptr.
         */
        explicit KeyPressFilter(QObject *parent = nullptr) : QObject(parent) {}

    public slots:
        /**
         * @brief Метод для фильтрации событий.
         * Обрабатывает события нажатия клавиш и перенаправляет их родительскому объекту.
         * @param obj Указатель на объект, которому принадлежит событие.
         * @param event Указатель на событие, которое нужно обработать.
         * @return true, если событие обработано; false в противном случае.
         */
        bool eventFilter(QObject *obj, QEvent *event) override
        {
            // Проверяем, является ли событие нажатием клавиши
            if (event->type() == QEvent::KeyPress) {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                // Перенаправляем событие родителю
                qApp->sendEvent(parent(), keyEvent); 
                return true; // Событие обработано
            }
            // Передаем событие дальше, если оно не было обработано
            return QObject::eventFilter(obj, event);
        }
    };

} // namespace Tetris::View::Qt
