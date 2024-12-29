#pragma once

#include <Model/Export.h>

#include <Model/Precompile.h>
#include <Model/Types.h>


namespace Tetris::Model::Blocks
{
    /// @brief Состояние фигуры
    enum class State : int
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
        using StateToPositions = std::unordered_map<State, Positions>;

        /// @brief Тип состояния - смещения
        using StateToOffsets = std::unordered_map<State, Offsets>;

        /// @brief Дефолдный конструктор
        AbstractBlock(TypeColor color);

        /// @brief Виртуальный деструктор
        virtual ~AbstractBlock() = default;

        /// @brief Вернуть цвет блока
        /// @return Цвет блока 
        TypeColor GetColor() const;

        virtual TypeBlock GetType() const
        {
            return TypeBlock::None;
        }

        /// @brief Получить текущее положение блока
        /// @return Описание блока
        Positions GetCurrentDescription();

        /// @brief Получить положение блока по состоянию блока
        /// @param state Состояние блока
        /// @return Положение блока
        Positions GetDescription(State state);

        /// @brief Получить текущее состояние блока
        /// @return состояние блока
        State GetCurrentState() const;

        /// @brief Получить следующее состояние блока по переданной команде
        /// @param cmd Команда
        /// @return Состояние
        State GetNextState(Command cmd) const;

        /// @brief Получить смещение для блока
        /// @param from Начальное состояние 
        /// @param to К которому необходимо прийти
        /// @return Смещения
        Offsets GetOffsets(State from, State to);

        /// @brief Повернуть блок
        void RotateBlock(Command cmd);

    protected:
        /// @brief Контейнер состояние - положение
        StateToPositions _stateToPositions;

        /// @brief Контейнер состояние - смещение
        StateToOffsets _stateToOffset;

    private:
        /// @brief Состояние блока
        State _state { State::Up };

        /// @brief Цвет блока
        TypeColor _color; 
    };

    inline const AbstractBlock::StateToOffsets JLSTZOffset
    {
        { State::Up, { Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0) } },
        { State::Right, { Position(0, 0), Position(1, 0), Position(1, -1), Position(0, 2), Position(1, 2) } },
        { State::Down, { Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0) } },
        { State::Left, { Position(0, 0), Position(-1, 0), Position(-1, -1), Position(0, 2), Position(-1, 2) } }
    };

    inline const AbstractBlock::StateToOffsets IOffset
    {
        { State::Up, { Position(0, 0), Position(-1, 0), Position(2, 0), Position(-1, 0), Position(2, 0) } },
        { State::Right, { Position(-1, 0), Position(0, 0), Position(0, 0), Position(0, 1), Position(0, -2) } },
        { State::Down, { Position(-1, 1), Position(1, 1), Position(-2, 1), Position(1, 0), Position(-2, 0) } },
        { State::Left, { Position(0, 1), Position(0, 1), Position(0, 1), Position(0, -1), Position(0, 2) } }
    };

    inline const AbstractBlock::StateToOffsets OOffset
    {
        { State::Up, { Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0) } },
        { State::Right, { Position(0, -1), Position(0, -1), Position(0, -1), Position(0, -1), Position(0, -1) } },
        { State::Down, { Position(-1, -1), Position(-1, -1), Position(-1, -1), Position(-1, -1), Position(-1, -1) } },
        { State::Left, { Position(-1, 0), Position(-1, 0), Position(-1, 0), Position(-1, 0), Position(-1, 0) } }
    };
} // namespace Tetris::Model::Blocks