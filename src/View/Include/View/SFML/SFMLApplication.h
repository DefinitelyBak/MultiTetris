#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <Model/AbstractModel.h>
#include <View/AbstractApplication.h>
#include <View/SFML/Widget.h>


namespace Tetris::View::SFML
{
    /// @brief Класс, реализующий интерфейс IApplication для графического приложения на базе SFML.
    class VIEW_EXPORT SFMLApplication final: public AbstractApplication
    {
    public:
        /// @brief Конструктор.
        /// @param model Указатель на модель приложения.
        /// @param countWidgets Количество виджетов, которые необходимо создать.
        /// @param fontPath Путь к файлу шрифта.
        SFMLApplication(AbstractModelPtr model, unsigned int countWidgets, const std::string& fontPath);
        
    private:
        /// @brief Запускает основной цикл приложения.
        void Run() override;

        /// @brief Создает виджеты приложения.
        void CreateWidgets();

        /// @brief Обновляет состояние виджетов.
        void UpdateWidgets();

        std::string _pathFont; ///< Путь к шрифту.
        unsigned int _count; ///< Количество виджетов.
        std::list<SFMLWidgetPtr> _widgets; ///< Список виджетов.
        AbstractModelPtr _model; ///< Указатель на модель приложения.
    };
} // namespace Tetris::View::SFML
