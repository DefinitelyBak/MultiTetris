#pragma once

#include <Model/Export.h>

#include <Model/Precompile.h>
#include <Model/Types.h>


namespace Tetris::Model::Blocks
{
    /// @brief Оринетации фигуры
    enum class Orientation : int
    {
        Up,
        Right,
        Down,
        Left
    };

    /// @brief Базовый класс блока 
    class MODEL_EXPORT AbstractBlock
    {
    public:
        /// @brief Тип состояния - описание блока
        using OrientationToPositions = std::unordered_map<Orientation, Positions>;

        /// @brief Тип состояния - смещения
        using OrientationToOffsets = std::unordered_map<Orientation, Offsets>;

        /// @brief Дефолдный конструктор
        AbstractBlock(TypeColor color);

        /// @brief Виртуальный деструктор
        virtual ~AbstractBlock() = default;

        /// @brief Вернуть цвет блока
        /// @return Цвет блока 
        [[nodiscard]] TypeColor GetColor() const;

        /// @brief Получить тип блока
        /// @return Тип блока
        [[nodiscard]] virtual TypeBlock GetType() const;

        /// @brief Получить текущее положение тетрамино блока
        /// @param orientation Необязательный параметр, при какой ориентации получить положение, по умочанию текущее положение
        /// @return Положение тетрамино блока
        [[nodiscard]] Positions GetFields(std::optional<Orientation> orientation = std::optional<Orientation>()) const;

        /// @brief Получить текущее состояние блока
        /// @param cmd Необязательный параметр, при какой комманде будет ориентация
        /// @return Ориентация
        [[nodiscard]] Orientation GetOrientatio(std::optional<Command> cmd = std::optional<Command>()) const;

        /// @brief Получить смещение для блока
        /// @param from Начальное состояние 
        /// @param to К которому необходимо прийти
        /// @return Смещения
        [[nodiscard]] Offsets GetOffsets(Orientation from, Orientation to) const;

        /// @brief Повернуть блок
        void RotateBlock(Command cmd);

    protected:
        /// @brief Контейнер состояние - положение
        OrientationToPositions _orientationToPositions;

        /// @brief Контейнер состояние - смещение
        OrientationToOffsets _orientationToOffset;

    private:
        /// @brief Состояние блока
        Orientation _orientation { Orientation::Up };

        /// @brief Цвет блока
        TypeColor _color; 
    };

    inline const AbstractBlock::OrientationToOffsets JLSTZOffset
    {
        { Orientation::Up, { Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0) } },
        { Orientation::Right, { Position(0, 0), Position(1, 0), Position(1, -1), Position(0, 2), Position(1, 2) } },
        { Orientation::Down, { Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0) } },
        { Orientation::Left, { Position(0, 0), Position(-1, 0), Position(-1, -1), Position(0, 2), Position(-1, 2) } }
    };

    inline const AbstractBlock::OrientationToOffsets IOffset
    {
        { Orientation::Up, { Position(0, 0), Position(-1, 0), Position(2, 0), Position(-1, 0), Position(2, 0) } },
        { Orientation::Right, { Position(-1, 0), Position(0, 0), Position(0, 0), Position(0, 1), Position(0, -2) } },
        { Orientation::Down, { Position(-1, 1), Position(1, 1), Position(-2, 1), Position(1, 0), Position(-2, 0) } },
        { Orientation::Left, { Position(0, 1), Position(0, 1), Position(0, 1), Position(0, -1), Position(0, 2) } }
    };

    inline const AbstractBlock::OrientationToOffsets OOffset
    {
        { Orientation::Up, { Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0) } },
        { Orientation::Right, { Position(0, -1), Position(0, -1), Position(0, -1), Position(0, -1), Position(0, -1) } },
        { Orientation::Down, { Position(-1, -1), Position(-1, -1), Position(-1, -1), Position(-1, -1), Position(-1, -1) } },
        { Orientation::Left, { Position(-1, 0), Position(-1, 0), Position(-1, 0), Position(-1, 0), Position(-1, 0) } }
    };
} // namespace Tetris::Model::Blocks