#pragma once

#include "Precompile.h"

#include "SFMLMap.h"
#include "Types.h"


namespace Tetris::View
{

    class SFMLPreviewBlock final : public sf::Drawable, public sf::Transformable
    {
        public:
            SFMLPreviewBlock(sf::Vector2f windowSize, bool withBorder = false);

            void SetBlock(Model::IdShape TypeBlock, Model::TypeColor color);

            Model::IdShape GetType() const;

        private:

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            SFMLMap _map;

            sf::Vector2f _windowSize;

            Model::IdShape _typeShape{Model::IdShape::None};
    };
}