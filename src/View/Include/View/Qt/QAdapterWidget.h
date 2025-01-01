#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <View/Qt/Widget.h>
#include <View/Qt/KeyPressFilter.h>
#include <Controller/MoveController.h>


namespace Tetris::View::Qt
{
    /// @brief Класс Adapter, который управляет виджетами и их обновлениями.
    class VIEW_EXPORT Adapter final: public QObject
    {
        Q_OBJECT
    public:
        /// @brief Конструктор класса Adapter
        /// @param model Указатель на модель, с которой будет работать адаптер
        Adapter(AbstractModelPtr model): _controller(model) {}

        /// @brief Создание нового виджета
        void CreateWidget()
        {
            Widget* widget = new Widget();
            SetConnection(widget);
            widget->show();
        }

        /// @brief Закрытие всех виджетов
        void CloseWidgets()
        {
            emit signalCloseWidget();
        }

        /// @brief Обновление виджетов на основе описания модели
        /// @param desc Описание текущего состояния модели
        void UpdateWidgets(DescriptionModelPtr desc)
        {
            emit signalUpdateWidget(desc);
        }

    public slots:
        /// @brief Слот для обновления модели на основе команды
        /// @param cmd Команда для обновления модели
        void SlotUpdateModel(Model::Command cmd)
        {
            _controller.Move(cmd);
        }

    signals:
        /// @brief Сигнал для обновления виджетов
        void signalUpdateWidget(DescriptionModelPtr desc);
        /// @brief Сигнал для закрытия виджетов
        void signalCloseWidget();

    private:
        /// @brief Установка соединений сигналов и слотов для виджета
        /// @param ptr Указатель на виджет
        void SetConnection(Widget* ptr)
        {
            connect(this, &Adapter::signalCloseWidget, ptr, &Widget::close);
            connect(this, &Adapter::signalUpdateWidget, ptr, &Widget::SlotUpdateView);
            connect(ptr, &Widget::SignalUpdateModel, this, &Adapter::SlotUpdateModel);
        }

        Controller::MoveController _controller; ///< Контроллер для управления движением
    };


    /// @brief Класс QAdapterWidget, который является абстрактным виджетом и использует адаптер
    class QAdapterWidget: public Model::AbstractWidget
    {
    public:
        /// @brief Конструктор класса QAdapterWidget
        /// @param model Указатель на модель, с которой будет работать виджет
        QAdapterWidget(AbstractModelPtr model): AbstractWidget(), _adapter(new Adapter(model)) {}

        /// @brief Обновление виджета (переопределение)
        void Update() override {}

        /// @brief Обновление виджета на основе описания модели
        /// @param descp Описание текущего состояния модели
        virtual void SlotUpdateWidget(DescriptionModelPtr descp) override
        {
            _adapter->UpdateWidgets(descp);
        }

        /// @brief Проверка, открыт ли виджет
        /// @return true, если виджет открыт
        bool IsOpen() const override
        {
            return true; // Здесь можно добавить логику для проверки состояния
        }

        /// @brief Закрытие виджета
        virtual void SlotCloseWidget() override
        {
            _adapter->CloseWidgets();
        }

        /// @brief Создание нового виджета
        void CreateWidget()
        {
            _adapter->CreateWidget();
        }

    private:
        Adapter* _adapter; ///< Указатель на адаптер
    };
}