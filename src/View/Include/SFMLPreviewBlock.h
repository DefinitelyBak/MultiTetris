#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "SFMLMap.h"

#include "Types.h"


namespace Tetris::View
{

    class SFMLPreviewBlock: public sf::Drawable, public sf::Transformable
    {
        public:
            /// @brief Конструкторк
            /// @param windowSize 
            /// @param rows 
            /// @param column 
            SFMLPreviewBlock(sf::Vector2f windowSize, bool withBorder = false);

            /// @brief 
            /// @param typeColor 
            void SetType(Model::IdShape TypeBlock);

            /// @brief 
            /// @return 
            Model::IdShape GetType() const;

        private:
            /// @brief Отрисовка
            /// @param target 
            /// @param states 
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            /// @brief Карта
            SFMLMap _map;

            /// @brief Размер окна отображения
            sf::Vector2f _windowSize;

            Model::IdShape _typeShape{Model::IdShape::None};
    };
}