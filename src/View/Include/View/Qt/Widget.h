#pragma once

#include <View/Export.h>
#include <View/Precompile.h>
#include <View/Forwards.h>

#include <Model/AbstractModel.h>
#include <Controller/MoveController.h>
#include <View/Qt/Map.h>
#include <View/Qt/WidgetPreviewBlock.h>


namespace Tetris::View::Qt
{
    /// @class Widget
    /// @brief Класс, представляющий виджет для отображения игры Tetris.
    /// Состояние карты меняется только из методов UpdateView, 
    /// просто надо какие события создают перерисовку содержимого.   
    class VIEW_EXPORT Widget final: public QWidget
    {
        Q_OBJECT 

    public:
        /// @brief Конструктор класса Widget.
        /// Инициализирует родительский виджет.
        /// @param parent Указатель на родительский виджет, по умолчанию nullptr.
        Widget(AbstractModelPtr model, QWidget* parent = nullptr);

        /// @brief Слот для обновления представления на основе модели описания.
        /// @param descp Модель описания, используемая для обновления представления.
        void SetMementoModel(MementoModelPtr descp);

    protected:
        /// @brief Обрабатывает события нажатия клавиш.
        /// Переопределяет метод keyPressEvent для обработки нажатий клавиш.
        /// @param event Указатель на событие нажатия клавиши.
        void keyPressEvent(QKeyEvent *event) override;

        /// @brief Обрабатывает события перерисовки виджета.
        /// Переопределяет метод paintEvent для обновления содержимого виджета.
        /// @param event Указатель на событие перерисовки.        
        void paintEvent(QPaintEvent *event) override;

    private:
        /// @brief Настраивает контейнер для карты.
        /// Выполняет инициализацию и настройку контейнера карты.
        void SetupMapContainer();

        /// @brief Настраивает контейнер для предварительного блока.
        /// Выполняет инициализацию и настройку контейнера предварительного блока.
        void SetupPreviewContainer();

        /// @brief Создает шрифт для отображения счета.
        /// @return Созданный объект QFont для отображения счета.        
        [[nodiscard]] QFont CreateScoreFont();

        /// @brief Создает метку для отображения счета.
        /// @return Указатель на созданный объект QLabel для отображения счета.
        [[nodiscard]] QLabel* CreateScoreLabel();

    private:
        Controller::MoveController _controller; ///< Указатель на объект карты

        Map* _map; ///< Указатель на объект карты
        QLabel* _text; ///< Указатель на метку для отображения счета
        WidgetPreviewBlock* _preview; ///< Указатель на объект предварительного блока

        MementoModelPtr _mementoModel{nullptr}; ///< Модель описания состояния игры
    };
} // namespace Tetris::View::Qt

