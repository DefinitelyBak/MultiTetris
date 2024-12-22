#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include "AbstractModel.h"
#include "MoveController.h"
#include "Qt/Map.h"
#include "Qt/PreviewBlock.h"


namespace Tetris::View::Qt
{
    /**
     * @class Widget
     * @brief Класс, представляющий виджет для отображения игры Tetris.
     * Состояние карты меняется только из методов UpdateView, 
     * просто надо какие события создают перерисовку содержимого.
     */
    class Widget : public QWidget
    {
        Q_OBJECT 

    public:
        /**
         * @brief Конструктор класса Widget.
         * Инициализирует родительский виджет.
         * @param parent Указатель на родительский виджет, по умолчанию nullptr.
         */
        Widget(QWidget* parent = nullptr);

    protected:
        /**
         * @brief Обрабатывает события нажатия клавиш.
         * Переопределяет метод keyPressEvent для обработки нажатий клавиш.
         * @param event Указатель на событие нажатия клавиши.
         */
        void keyPressEvent(QKeyEvent *event) override;

        /**
         * @brief Обрабатывает события перерисовки виджета.
         * Переопределяет метод paintEvent для обновления содержимого виджета.
         * @param event Указатель на событие перерисовки.
         */
        void paintEvent(QPaintEvent *event) override;

    private:
        /**
         * @brief Настраивает контейнер для карты.
         * Выполняет инициализацию и настройку контейнера карты.
         */
        void setupMapContainer();

        /**
         * @brief Настраивает контейнер для предварительного блока.
         * Выполняет инициализацию и настройку контейнера предварительного блока.
         */
        void setupPreviewContainer();

        /**
         * @brief Создает шрифт для отображения счета.
         * @return Созданный объект QFont для отображения счета.
         */
        QFont createScoreFont();

        /**
         * @brief Создает метку для отображения счета.
         * @return Указатель на созданный объект QLabel для отображения счета.
         */
        QLabel* createScoreLabel();

    public slots:
        /**
         * @brief Слот для обновления представления на основе модели описания.
         * @param descp Модель описания, используемая для обновления представления.
         */
        void SlotUpdateView(Model::DescriptionModel descp);

        /**
         * @brief Получает текущее состояние модели описания.
         * @return Текущая модель описания состояния игры.
         */
        Model::DescriptionModel GetDescriptionModel();

    signals:
        /**
         * @brief Сигнал для обновления модели с командой.
         * @param command Команда для обновления модели.
         */
        void SignalUpdateModel(Model::Command command);

    private:
        Map* _map; ///< Указатель на объект карты

        QLabel* _text; ///< Указатель на метку для отображения счета
        
        PreviewBlock* _preview; ///< Указатель на объект предварительного блока
        std::mutex _mutex; ///< Мьютекс для синхронизации доступа к данным
        Model::DescriptionModel _descriptionModel; ///< Модель описания состояния игры
    };
} // namespace Tetris::View::Qt

