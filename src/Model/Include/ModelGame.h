#pragma once

#include "Precompile.h" 
#include "Forwards.h"

#include "Types.h"

#include "AbstractModel.h"

#include "Map.h"
#include "Factory/ShapeFactory.h"

#include "AbstractWidget.h"

#include <boost/signals2.hpp>



namespace Tetris::Model
{

    /// @brief Модель игры
    class ModelGame final: public AbstractModel
    {
    public:
        /// @brief Конструктор по умолчанию
        ModelGame();

        /// @brief 
        /// @param command 
        void SlotUpdate(Command command) override;

        void SetView(AbstractWidgetPtr view) override;

        /// @brief Сигнал на обновление карты
        boost::signals2::signal<void(Tetris::Model::DescriptionMap)> SignalUpdateView; 

        boost::signals2::signal<void(Tetris::Model::DescriptionBlock)> SignalSetNextBlock;

        boost::signals2::signal<void(unsigned int)> SignalSetScore;

    private:
        /// @brief 
        /// @param lines 
        void AddScore(unsigned int lines);

        /// @brief Создание случайного блока
        /// @return Новый блок
        AbstractBlockPtr CreateRandomBlock(); 

        Map _map;
        Blocks::BlocksFactory _factory;

        unsigned int _score{0};

        IdShape _lastTypeBlock{IdShape::None};
        TypeColor _lasTypeColor{TypeColor::None};

        std::random_device _device;
        std::mt19937 _randomEngine;

        AbstractBlockPtr _currentBlock;
        AbstractBlockPtr _nextBlock;
    };

}