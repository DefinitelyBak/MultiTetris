#pragma once

#include "Precompile.h"
#include "Types.h"


namespace Tetris::Model
{
    /// @brief Интерфейс для виджетов в игре Тетрис
    class AbstractWidget
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
        virtual void SlotUpdateWidget(Model::DescriptionModel descp)
        {
            std::scoped_lock<std::mutex> l(_mutex);
            _descriptionModel = descp;
        }

        /// @brief Обновление виджета на основе описания модели
        /// @return descp Описание текущего состояния модели
        Model::DescriptionModel GetDescriptionModel()
        {
            std::scoped_lock<std::mutex> l(_mutex);
            return _descriptionModel;
        }

    private:
        std::mutex _mutex;
        Model::DescriptionModel _descriptionModel;
    };
} // namespace Tetris::Model