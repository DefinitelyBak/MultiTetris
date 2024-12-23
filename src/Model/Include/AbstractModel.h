#pragma once

#include "precompile.h"

#include "Forwards.h"
#include "Types.h"

#include "DescriptionModel.h"
#include "AbstractWidget.h"


namespace Tetris::Model
{
    /// @brief Абстрактный класс модели для управления игровыми данными
    class AbstractModel
    {
    public:
        /// @brief Сигнал для обновления виджетов с описанием модели
        using TypeSignalUpdateWidgets = boost::signals2::signal<void(DescriptionModelPtr)>;
        /// @brief Сигнал для закрытия виджетов
        using TypeSignalCloseWidgets = boost::signals2::signal<void()>;

        /// @brief Конструктор
        AbstractModel() : _stack(128), _finish(false)
        {
            StartModel();
        }

        /// @brief Деструктор
        virtual ~AbstractModel()
        {
            StopModel();
            SignalCloseWidgets();
        }

        /// @brief Метод для обновления модели с полученной командой
        /// @param command Команда для обновления
        void SlotUpdate(Command command)
        {
            while (!_stack.push(command));
        }

        /// @brief Установка виджета для обновления и закрытия
        /// @param view Указатель на виджет
        void SetWidget(AbstractWidgetPtr view)
        {
            SignalUpdateWidgets.connect(TypeSignalUpdateWidgets::slot_type(&AbstractWidget::SlotUpdateWidget, view.get(), boost::placeholders::_1).track_foreign(view));
            SignalCloseWidgets.connect(TypeSignalCloseWidgets::slot_type(boost::bind(&AbstractWidget::SlotCloseWidget, view.get())).track_foreign(view));
        }

    protected:
        TypeSignalUpdateWidgets SignalUpdateWidgets; ///< Сигнал для обновления виджетов
        TypeSignalCloseWidgets SignalCloseWidgets; ///< Сигнал для закрытия виджетов

        /// @brief Чисто виртуальный метод для обновления модели
        /// @param command Команда для обновления
        /// @param desc Ссылка на описание модели
        virtual void UpdateModel(Command command, DescriptionModelPtr& desc) = 0;

    private:
        /// @brief Запуск рабочего потока модели
        void StartModel()
        {
            _worker = std::thread(&AbstractModel::Run, this); // Создание и запуск потока
        }

        /// @brief Остановка рабочего потока модели
        void StopModel()
        {
            _finish = true;
            _worker.join();
        }

        /// @brief Основной рабочий метод, выполняющий обновления модели
        void Run()
        {
            Command cmd;
            while (!_finish)
            {
                if (_stack.pop(cmd))
                {
                    DescriptionModelPtr desc = std::make_shared<Model::DescriptionModel>();
                    UpdateModel(cmd, desc);
                    SignalUpdateWidgets(desc);
                }
            }
        }
        
        std::thread _worker; ///< Рабочий поток
        std::atomic<bool> _finish; ///< Флаг завершения работы модели
        boost::lockfree::stack<Command> _stack; ///< Неблокирующий стек для команд
    };
} // namespace Tetris::Model