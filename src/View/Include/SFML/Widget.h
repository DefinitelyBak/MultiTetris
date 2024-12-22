#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include "AbstractWidget.h"
#include "AbstractModel.h"
#include "MoveController.h"
#include "Map.h"
#include "Text.h"
#include "WidgetPreviewBlock.h"


namespace Tetris::View::SFML
{
    // Класс Widget представляет собой графический интерфейс для игры Tetris,
    // реализующий методы для отображения и обновления состояния игры.
    class Widget final : public Model::AbstractWidget 
    {
    public:
        // Конструктор класса, инициализирующий виджет с моделью и путем к шрифту.
        Widget(AbstractModelPtr model, const std::string& pathFont);

        // Деструктор класса, по умолчанию.
        ~Widget() override = default;

        // Метод для обновления состояния виджета, вызывается в каждом кадре.
        void Update() override;

        // Метод для проверки, открыт ли виджет.
        bool IsOpen() const override;

        // Метод для закрытия виджета.
        void SlotCloseWidget() override;

    private:
        // Метод для инициализации отображения счета.
        void InitializeScore();

        // Метод для инициализации блока предварительного просмотра.
        void InitializePreviewBlock();

        // Метод для обработки событий ввода от пользователя.
        void HandleEvents();

        // Метод для обработки нажатий клавиш.
        void HandleKeyPress(sf::Keyboard::Scancode scancode);

        // Метод для обновления карты на основе состояния модели.
        void UpdateMap(const Model::DescriptionModel& descriptionModel);

        // Метод для обновления блока предварительного просмотра.
        void UpdatePreviewBlock(const Model::DescriptionModel& descriptionModel);

        // Метод для обновления отображаемого счета.
        void UpdateScore(const Model::DescriptionModel& descriptionModel);

        // Метод для отрисовки всех компонентов виджета на экране.
        void Render();

    private:
        sf::RenderWindow _window; //< Окно для рендеринга графики.

        Controller::MoveController _controller; //< Контроллер для управления движением объектов в игре.
        Map _map; //< Объект карты, отображающий игровое поле.
        WidgetPreviewBlock _previewBlock; //< Виджет отобраения следующего блока.
        Text _score; //< Объект для отображения текущего счета игрока.

        std::atomic<bool> _windowOpen{true}; //< Флаг, указывающий, открыто ли окно.
    };
}// namespace Tetris::View::SFML
