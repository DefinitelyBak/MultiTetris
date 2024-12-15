#pragma once

#include "Precompile.h"

#include "Qt/Map.h"
#include "Types.h"


namespace Tetris::View::Qt
{

    class PreviewBlock final : public Map
    {
        Q_OBJECT
        public:
            PreviewBlock(QWindow* parent = nullptr, bool withBorder = false);

            void SetBlock(Model::IdShape TypeBlock, Model::TypeColor color);

            Model::IdShape GetType() const;

        private:

            Model::IdShape _typeShape{Model::IdShape::None};
    };
}