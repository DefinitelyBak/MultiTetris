#pragma once

#include <Model/Precompile.h>
#include <Model/Types.h>


namespace Tetris::Model::Blocks
{
    /// @brief Абстрактный создатель для создания объектов.
    /// @tparam Base Базовый класс создаваемых объектов.
    template <class Base>
    class MODEL_EXPORT AbstractCreator
    {
    public:
        /// @brief Конструктор по умолчанию.
        AbstractCreator() {}

        /// @brief Виртуальный деструктор.
        virtual ~AbstractCreator() {}

        /// @brief Создать объект с заданным цветом.
        /// @param color Цвет создаваемого объекта.
        /// @return Указатель на созданный объект.
        [[nodiscard]] virtual Base* Create(TypeColor color) const = 0;
    };

    /// @brief Реализация создателя для конкретного типа объекта.
    /// @tparam C Тип создаваемого объекта.
    /// @tparam Base Базовый класс создаваемых объектов.
    template <class C, class Base>
    class Creator final : public AbstractCreator<Base>
    {
    public:
        /// @brief Конструктор по умолчанию.
        Creator() {}

        /// @brief Виртуальный деструктор.
        virtual ~Creator() {}

        /// @brief Создать объект с заданным цветом.
        /// @param color Цвет создаваемого объекта.
        /// @return Указатель на созданный объект.
        [[nodiscard]] Base* Create(TypeColor color) const override { return new C(color); }
    };
} // namespace Tetris::Model::Blocks
