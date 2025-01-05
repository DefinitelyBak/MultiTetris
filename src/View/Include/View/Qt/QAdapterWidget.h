#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <View/Qt/Widget.h>
#include <View/Qt/KeyPressFilter.h>
#include <Controller/MoveController.h>


namespace Tetris::View::Qt
{
    /// @brief Класс QAdapterWidget qt адаптер для игры 
    class QAdapterWidget: public Model::AbstractWidget
    {
    public:
        /// @brief Конструктор класса QAdapterWidget
        /// @param model Модель игры
        QAdapterWidget(AbstractModelPtr model): AbstractWidget(), _widget(new Widget(model))
        {
            _widget->show();
        }

        /// @brief Обновление виджета на основе описания модели
        /// @param memento Снимок текущего состояния модели
        virtual void SlotUpdateWidget(MementoModelPtr memento) override
        {
            if (_widget->isVisible())
                _widget->SetMementoModel(memento);
        }

        /// @brief Проверка, открыт ли виджет
        /// @return true, если виджет открыт
        [[nodiscard]] bool IsOpen() const override
        {
            return _open; // Здесь можно добавить логику для проверки состояния
        }

        /// @brief Закрытие виджета
        virtual void SlotCloseWidget() override
        {
            _open = false;
            _widget->close();
        }

    private:
        Widget* _widget;
        bool _open{ true };
    };
}