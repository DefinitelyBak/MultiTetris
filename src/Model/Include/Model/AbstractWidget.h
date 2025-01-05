#pragma once

#include <Model/Precompile.h>
#include <Model/Export.h>
#include <Model/Forwards.h>

#include <Model/Types.h>


namespace Tetris::Model
{
    /// @brief Интерфейс для виджетов в игре Тетрис
    class MODEL_EXPORT AbstractWidget
    {
    public:
        /// @brief Деструктор по умолчанию
        virtual ~AbstractWidget() = default;

        /// @brief Проверка, открыт ли виджет
        /// @return true, если виджет открыт; иначе false
        [[nodiscard]] virtual bool IsOpen() const = 0;

        /// @brief Закрытие виджета
        virtual void SlotCloseWidget() = 0;

        /// @brief Обновление виджета на основе снимка модели
        /// @param memento Снимок текущего состояния модели
        virtual void SlotUpdateWidget(MementoModelPtr memento)
        {
            std::scoped_lock<std::mutex> l(_mutex);
            _mementoModel = memento;
        }

        /// @brief Получить снимок модели игры
        /// @return Снимок модели игры
        [[nodiscard]] MementoModelPtr GetMementoModel()
        {
            std::scoped_lock<std::mutex> l(_mutex);
            return _mementoModel;
        }

    private:
        std::mutex _mutex;
        MementoModelPtr _mementoModel;
    };
} // namespace Tetris::Model