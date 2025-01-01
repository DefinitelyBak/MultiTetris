#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <Model/AbstractWidget.h>
#include <Model/AbstractModel.h>
#include <Controller/MoveController.h>
#include <View/SFML/Map.h>
#include <View/SFML/Text.h>
#include <View/SFML/WidgetPreviewBlock.h>


namespace Tetris::View::SFML
{
    /// @brief Класс Widget представляет собой графический интерфейс для игры Tetris,
    /// реализующий методы для отображения и обновления состояния игры
    class VIEW_EXPORT Widget final : public Model::AbstractWidget
    {
    public:
        /// @brief Конструктор класса, инициализирующий виджет с моделью и путем к шрифту
        /// @param model Модель игры
        /// @param pathFont Путь до шрифта
        Widget(AbstractModelPtr model, const std::string& pathFont);

        /// @brief Деструктор класса, по умолчанию
        ~Widget() override = default;

        /// @brief Метод для обновления состояния виджета, вызывается в каждом кадре
        void Update() override;

        /// @brief Метод для проверки, открыт ли виджет 
        bool IsOpen() const override;

        /// @brief Метод для закрытия виджета 
        void SlotCloseWidget() override;

    private:
        /// @brief Метод для инициализации отображения счета 
        void InitializeScore();

        /// @brief Метод для инициализации блока предварительного просмотра 
        void InitializePreviewBlock();

        /// @brief Метод для обработки событий ввода от пользователя 
        void HandleEvents();

        /// @brief Метод для обработки нажатий клавиш 
        /// @param scancode Код клавиши
        void HandleKeyPress(sf::Keyboard::Scancode scancode);

        /// @brief Метод для обновления карты на основе состояния модели 
        /// @param descriptionModel Описание модели
        void UpdateMap(const DescriptionModelPtr& descriptionModel);

        /// @brief Метод для обновления блока предварительного просмотра
        /// @param descriptionModel Описание модели 
        void UpdatePreviewBlock(const DescriptionModelPtr& descriptionModel);

        /// @brief Метод для обновления отображаемого счета
        /// @param descriptionModel Описание модели 
        void UpdateScore(const DescriptionModelPtr& descriptionModel);

        /// @brief Метод для отрисовки всех компонентов виджета на экране 
        void Render();

    private:
        sf::RenderWindow _window; //< Окно для рендеринга графики 

        Controller::MoveController _controller; //< Контроллер для управления движением объектов в игре 
        Map _map; //< Объект карты, отображающий игровое поле 
        WidgetPreviewBlock _previewBlock; //< Виджет отобраения следующего блока 
        Text _score; //< Объект для отображения текущего счета игрока 

        std::atomic<bool> _windowOpen{true}; //< Флаг, указывающий, открыто ли окно 
    };
}// namespace Tetris::View::SFML
