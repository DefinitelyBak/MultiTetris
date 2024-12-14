#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include "AbstractModel.h"
#include "MoveController.h"

#include <QWidget>
#include <QObject>

#include "Precompile.h"
#include "Types.h"

#include <QWindow>
#include <QBackingStore>
#include <QObject>


namespace Tetris::View::Qt
{
    /// @brief Метод конвертации TypeColor в sf::Color
    /// @param color Цвет
    /// @return Цвет sf::Color
    QColor ColorFromTypeColor(Model::TypeColor color);

    class Map: public QWindow
    {
        Q_OBJECT
    public:
        /// @brief Конструкторк
        /// @param withBorder С рамкой
        Map(QWindow *parent, bool withBorder);

        /// @brief Установить карту
        /// @param map Карта с блоками
        /// @param rows Кол-вл строк на карте
        /// @param columns Кол-во столбцов на карте
        void SetMap(Model::DataMap map, int rows, int columns);

    protected: // Начало секции полей и методов, доступных только в наследниках этого класса

        // Ниже перегружены полиморфные методы родительского класса QWindow
        // Библиотека Qt рассылает различные события по этим методам
        //  - метод event вызывается перед обработкой любых событий, включая resizeEvent и exposeEvent
        //  - метод resizeEvent вызывается при изменении размера окна
        //  - метод exposeEvent вызывается при показе окна
        bool event(QEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
        void exposeEvent(QExposeEvent *event) override;

    private:
        void renderLater();
        void renderNow();
        void render(QPainter *painter);

        // Класс QBackingStore предоставляет окну буфер рисования кадра.
        // Грубо говоря, этот буфер содержит будущие пиксели окна и позволяет
        //  рисовать векторную графику (фигуры, изображения, текст), заполняя
        //  этот буфер пикселей.
        QBackingStore *m_backingStore = nullptr;

        /// @brief Карта
        Model::DataMap _map;

        /// @brief Размер окна отображения
        sf::Vector2f _windowSize;

        int _rows;
        int _columns;

        float _offsetX;
        float _offsetY;

        float _borderWidth{0};

        QVector<QRect> _borders;
    };
}