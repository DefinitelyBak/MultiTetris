#pragma once

#include <View/Export.h>
#include <View/Precompile.h>
#include <Model/Types.h>
#include <View/Forwards.h>

#include <Model/AbstractModel.h>


namespace Tetris::View::Qt
{
    /// @brief Метод конвертации TypeColor в QColor
    /// @param color Цвет в формате Model::TypeColor
    /// @return Цвет в формате QColor
    QColor ColorFromTypeColor(Model::TypeColor color);

    class VIEW_EXPORT Map: public QWindow
    {
        Q_OBJECT
    public:
        /// @brief Конструктор класса Map
        /// @param parent Указатель на родительское окно
        /// @param withBorder Флаг, указывающий, нужно ли отображать рамку
        Map(QWindow *parent, bool withBorder = false);

        /// @brief Установить карту
        /// @param map Вектор, представляющий карту с блоками
        /// @param size Размер карты (количество строк и столбцов)
        void SetMap(const std::vector<Model::TypeColor>& map, Model::MapSize size);

    protected:
        /// @brief Обработка событий
        /// @param event Указатель на событие
        /// @return true, если событие обработано
        bool event(QEvent *event) override;

        /// @brief Обработка изменения размера окна
        /// @param event Указатель на событие изменения размера
        void resizeEvent(QResizeEvent *event) override;

        /// @brief Обработка события отображения окна
        /// @param event Указатель на событие отображения
        void exposeEvent(QExposeEvent *event) override;

    private:
        /// @brief Запрос на отрисовку в будущем
        void renderLater();

        /// @brief Непосредственная отрисовка карты
        void renderNow();

        /// @brief Отрисовка карты с использованием QPainter
        /// @param painter Указатель на объект QPainter
        void render(QPainter *painter);

        /// @brief Обновление представления карты
        void UpdateView();

        /// @brief Инициализация границ карты
        void InitializeBorders();

        /// @brief Создание границы
        /// @param size Размер границы
        /// @param position Позиция границы
        /// @return Созданная граница в виде sf::RectangleShape
        sf::RectangleShape CreateBorder(const sf::Vector2f& size, const sf::Vector2f& position);

        /// @brief Обновление размеров полей карты
        void UpdateFieldSizes();

    private:
        QBackingStore *m_backingStore = nullptr; ///< Указатель на объект QBackingStore

        /// @brief Карта, представляющая блоки
        std::vector<Model::TypeColor> _map;

        /// @brief Размер окна отображения
        sf::Vector2f _windowSize;

        int _rows; ///< Количество строк в карте
        int _columns; ///< Количество столбцов в карте

        float _offsetX; ///< Смещение по оси X для отрисовки блоков
        float _offsetY; ///< Смещение по оси Y для отрисовки блоков

        float _borderWidth{0}; ///< Ширина границы карты

        QVector<QRect> _borders; ///< Вектор, содержащий границы карты
    };
}