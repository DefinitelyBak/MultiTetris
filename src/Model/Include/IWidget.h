#pragma once

#include "Types.h"


namespace Tetris::Model
{
    /// @brief Интерфейс для виджетов в игре Тетрис
    class IWidget
    {
    public:
        /// @brief Деструктор по умолчанию
        virtual ~IWidget() = default;

        /// @brief Обновление состояния виджета
        virtual void Update() = 0;

        /// @brief Обновление виджета на основе описания модели
        /// @param descp Описание текущего состояния модели
        virtual void SlotUpdateWidget(Model::DescriptionModel descp) = 0;

        /// @brief Проверка, открыт ли виджет
        /// @return true, если виджет открыт; иначе false
        virtual bool IsOpen() const = 0;

        /// @brief Закрытие виджета
        virtual void SlotCloseWidget() = 0;
    };
} // namespace Tetris::Model