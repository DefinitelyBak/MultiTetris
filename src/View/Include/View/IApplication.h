#pragma once


namespace Tetris::View
{
    /// @brief Интерфейсный класс приложения
    class IApplication
    {
    public:
        /// @brief Дефолтный деструктор
        virtual ~IApplication() = default;

        /// @brief Приложение выполняется
        virtual bool isExecution() const = 0;

    private:
        /// @brief Запуск приложения
        virtual void Run() = 0;
    };

} // namespace Tetris::View