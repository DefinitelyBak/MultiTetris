#pragma once

#include "Precompile.h" 

#include "AbstractObservable.h"
#include "AbstractObserver.h"
#include "Map.h"
#include "Factory/ShapeFactory.h"



namespace Tetris::Model
{

    class ModelGame: public Tetris::Common::AbstarctObserver, public Tetris::Common::AbstractObservable
    {
    public:
        /// @brief 
        ModelGame();

        ~ModelGame();

        /// @brief 
        void Update();

    private:
        /// @brief 
        /// @return 
        const std::shared_ptr<AbstractBlock> CreateRandomBlock(); 

        Map _map;
        Blocks::ShapeFactory _factory;

        IdShape _lastTypeBlock{IdShape::None};
        Color _lasTypeColor{Color::None};

        std::random_device _dev;
        std::mt19937 _rng;
        std::uniform_int_distribution<int> _dist7;
        std::uniform_int_distribution<int> _dist5;


    };

}