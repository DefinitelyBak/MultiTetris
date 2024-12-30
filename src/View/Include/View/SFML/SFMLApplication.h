#pragma once

#include <View/Export.h>
#include <View/Precompile.h>

#include <View/Forwards.h>
#include <Model/AbstractModel.h>
#include <View/IApplication.h>


namespace Tetris::View::SFML{
    /// @class SFMLApplication
    /// @brief Класс, реализующий интерфейс IApplication для графического приложения на базе SFML.
    class VIEW_EXPORT SFMLApplication final: public IApplication
    {
    public:
        /// @brief Конструктор.
        /// @param model Указатель на модель приложения.
        /// @param countWidgets Количество виджетов, которые необходимо создать.
        /// @param fontPath Путь к файлу шрифта.
        SFMLApplication(AbstractModelPtr model, unsigned int countWidgets, const std::string& fontPath);
        
        /// @brief Деструктор.
        ~SFMLApplication();

        /// @brief Запускает основной цикл приложения.
        void Run() override;

        /// @brief Проверяет, выполняется ли приложение.
        /// @return true, если приложение выполняется; false в противном случае.
        bool isExecution() const override; 

    private:
        /// @brief Создает виджеты приложения.
        void CreateWidgets();

        /// @brief Обновляет состояние виджетов.
        void UpdateWidgets();

        std::string _pathFont; ///< Путь к шрифту.
        unsigned int _count; ///< Количество виджетов.
        std::list<AbstractWidgetPtr> _widgets; ///< Список виджетов.
        AbstractModelPtr _model; ///< Указатель на модель приложения.
        std::thread _thread; ///< Поток для выполнения приложения.
        std::atomic<bool> _execution; ///< Флаг для управления выполнением приложения.
    };
} // namespace Tetris::View::SFML
