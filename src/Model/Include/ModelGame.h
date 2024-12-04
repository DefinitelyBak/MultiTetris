#pragma once

#include "Precompile.h" 

#include "Map.h"
#include "Factory/ShapeFactory.h"

#include <boost/signals2.hpp>

#include "C:\Projects\ProjectTetris\Tetris\src\view\Include\AbstractWidget.h"


namespace Tetris::Model
{

    /// @brief Модель игры
    class ModelGame
    {
    public:
        /// @brief Конструктор по умолчанию
        ModelGame();

        /// @brief 
        /// @param command 
        void SlotUpdate(Command command);

        void SetView(std::shared_ptr<View::AbstractWidget> view);

        /// @brief Сигнал на обновление карты
        boost::signals2::signal<void(DescriptionMap)> SignalUpdateView; 

    private:
        /// @brief 
        /// @param lines 
        void AddScore(unsigned int lines);

        /// @brief Создание случайного блока
        /// @return Новый блок
        std::shared_ptr<AbstractBlock> CreateRandomBlock(); 

        Map _map;
        Blocks::BlocksFactory _factory;

        unsigned int _score{0};

        IdShape _lastTypeBlock{IdShape::None};
        TypeColor _lasTypeColor{TypeColor::None};

        std::random_device _device;
        std::mt19937 _randomEngine;

        std::shared_ptr<AbstractBlock> _currentBlock;
        std::shared_ptr<AbstractBlock> _nextBlock;
    };

}