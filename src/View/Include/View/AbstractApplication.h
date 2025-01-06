#pragma once

#include <View/Forwards.h>
#include <View/Export.h>


namespace Tetris::View
{
    /// @brief Интерфейсный класс приложения
    class VIEW_EXPORT AbstractApplication
    {
    public:
        /// @brief Дефолтный конструктокр
        AbstractApplication(): _execution(true)
        {
            _thread = std::thread(&AbstractApplication::Run, this);
        }

        /// @brief Дефолтный деструктор
        virtual ~AbstractApplication()
        {
            _execution = false;
            if (_thread.joinable())
                _thread.join();
        }

        /// @brief Приложение выполняется
        [[nodiscard]] bool isExecution() const
        {
            return _execution;
        }

    private:
        /// @brief Запуск приложения
        virtual void Run() = 0;

    protected:
        std::atomic<bool> _execution; ///< Флаг для управления выполнением приложения.

    private:
        std::thread _thread; ///< Поток для выполнения приложения.
    };

} // namespace Tetris::View