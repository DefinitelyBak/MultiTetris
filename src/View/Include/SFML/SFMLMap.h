#pragma once

#include "Precompile.h"
#include "Types.h"


namespace Tetris::View
{
    /// @brief Метод конвертации TypeColor в sf::Color
    /// @param color Цвет
    /// @return Цвет sf::Color
    sf::Color ColorFromTypeColor(Model::TypeColor color);

    class SFMLMap: public sf::Drawable, public sf::Transformable
    {
        public:
            /// @brief Конструкторк
            /// @param windowSize Размер окна
            /// @param withBorder С рамкой
            SFMLMap(sf::Vector2f windowSize, bool withBorder = false);

            /// @brief Установить карту
            /// @param map Карта с блоками
            /// @param rows Кол-вл строк на карте
            /// @param columns Кол-во столбцов на карте
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

            int _rows;
            int _columns;

            float _offsetX;
            float _offsetY;

            float _borderWidth{0};

            std::list<sf::RectangleShape> _borders;
    };
}