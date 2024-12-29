#pragma once

#include <Model/Export.h>

#include <Model/Precompile.h>
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

        /// @brief Обновление состояния виджета
        virtual void Update() = 0;

        /// @brief Проверка, открыт ли виджет
        /// @return true, если виджет открыт; иначе false
        virtual bool IsOpen() const = 0;

        /// @brief Закрытие виджета
        virtual void SlotCloseWidget() = 0;

        /// @brief Обновление виджета на основе описания модели
        /// @param descp Описание текущего состояния модели
        virtual void SlotUpdateWidget(DescriptionModelPtr descp)
        {
            std::scoped_lock<std::mutex> l(_mutex);
            _descriptionModel = descp;
        }

        /// @brief Обновление виджета на основе описания модели
        /// @return descp Описание текущего состояния модели
        DescriptionModelPtr GetDescriptionModel()
        {
            std::scoped_lock<std::mutex> l(_mutex);
            return _descriptionModel;
        }

    private:
        std::mutex _mutex;
        DescriptionModelPtr _descriptionModel;
    };
} // namespace Tetris::Model