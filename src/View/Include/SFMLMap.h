#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "Types.h"


namespace Tetris::View
{
    /// @brief 
    /// @param color 
    /// @return 
    sf::Color ColorFromTypeColor(Model::TypeColor color);

    class SFMLMap: public sf::Drawable, public sf::Transformable
    {
        public:
            /// @brief Конструкторк
            /// @param windowSize 
            /// @param rows 
            /// @param column 
            SFMLMap(sf::Vector2f windowSize, bool withBorder = false);

            /// @brief 
            /// @param map 
            /// @param rows 
            /// @param columns 
            void SetMap(Model::DataMap map, int rows, int columns);

        private:
            /// @brief Отрисовка
            /// @param target 
            /// @param states 
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            /// @brief 
            void UpdateView();

            /// @brief Карта
            Model::DataMap _map;

            /// @brief Глупый алгоритм 
            std::vector<sf::RectangleShape> _filds;

            /// @brief Размер окна отображения
            sf::Vector2f _windowSize;

            /// @brief Колличество строк и столбцов.
            // СТРОКИ (для дураков)
            int _rows;
            // СТОЛБЦЫ (для дураков)
            int _columns;

            /// @brief Шаг между одним и другим элементом
            float _offsetX;
            float _offsetY;

            float _borderWidth{0};

            std::list<sf::RectangleShape> _borders;
    };
}