#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <Model/Types.h>


namespace Tetris::View::SFML
{
    /// @brief Метод конвертации TypeColor в sf::Color
    /// @param color Цвет из модели
    /// @return Цвет в формате sf::Color
    sf::Color ColorFromTypeColor(Model::TypeColor color);

    /// @brief Класс карты игры на основе SFML
    class VIEW_EXPORT Map final: public sf::Drawable, public sf::Transformable
    {
    public:
        /// @brief Конструктор класса Map
        /// @param windowSize Размер окна отображения
        /// @param withBorder Указывает, нужно ли отображать границы
        Map(sf::Vector2f windowSize, bool withBorder = false);

        /// @brief Установить карту
        /// @param map Вектор с цветами блоков
        /// @param size Размер карты (строки и столбцы)
        void SetMap(const std::vector<Model::TypeColor>& map, Model::MapSize size);

    private:
        /// @brief Отрисовка карты
        /// @param target Цель отрисовки
        /// @param states Состояния отрисовки
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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
        std::vector<Model::TypeColor> _map; //< Вектор с цветами блоков карты
        std::vector<sf::RectangleShape> _fields; //< Вектор с прямоугольниками для отображения блоков 

        sf::Vector2f _windowSize; //< Размер окна отображения
        int _rows; 
        int _columns; 
        float _offsetX;
        float _offsetY;

        float _borderWidth{0};

        std::list<sf::RectangleShape> _borders;
    };
} // namespace Tetris::View::SFML
