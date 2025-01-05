#pragma once

#include <View/Precompile.h>
#include <View/Export.h>

#include <Model/Types.h>
#include <Model/AbstractModel.h>
#include <View/Forwards.h>


namespace Tetris::View::Qt
{
    /// @brief Метод конвертации TypeColor в QColor
    /// @param color Цвет в формате Model::TypeColor
    /// @return Цвет в формате QColor
    [[nodiscard]] QColor ColorFromTypeColor(Model::TypeColor color);

    /// @brief Класс карты игры на основе Qt
    class VIEW_EXPORT Map: public QWidget
    {
        Q_OBJECT
    public:
        /// @brief Конструктор класса Map
        /// @param parent Указатель на родительское окно
        Map(QWidget* parent);

        /// @brief Установить карту
        /// @param map Вектор, представляющий карту с блоками
        /// @param size Размер карты (количество строк и столбцов)
        void SetMap(const std::vector<Model::TypeColor>& map, Model::MapSize size);

    protected:
        /// @brief Обработка события отображения окна
        /// @param event Указатель на событие отображения
        void paintEvent(QPaintEvent* event) override;

    private:
        /// @brief Непосредственная отрисовка карты
        void Render();

    private:
        /// @brief Карта, представляющая блоки
        std::vector<Model::TypeColor> _map;

        /// @brief Размер окна отображения
        sf::Vector2f _windowSize;

        int _rows; ///< Количество строк в карте
        int _columns; ///< Количество столбцов в карте

        float _offsetX; ///< Смещение по оси X для отрисовки блоков
        float _offsetY; ///< Смещение по оси Y для отрисовки блоков
    };
}