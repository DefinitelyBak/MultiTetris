#pragma once

#include "Precompile.h" 
#include "Forwards.h"

#include "Types.h"

#include "AbstractModel.h"

#include "Map.h"
#include "Factory/BlocksFactory.h"


namespace Tetris::Model
{

    /// @brief Модель игры
    class ModelGame final: public AbstractModel
    {
    public:
        /// @brief Конструктор по умолчанию
        ModelGame();

   protected:

        void UpdateModel(Command command, DescriptionModel& desc) override;

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

        std::random_device _device;
        std::mt19937 _randomEngine;

        //@TODO
        // Это надо исправить, тут дублирование информации. Исправим когда буду проихводить рефакторинг CreateRandomBlock
        AbstractBlockPtr _currentBlock;
        AbstractBlockPtr _nextBlock;

        IdShape _lastTypeBlock{IdShape::None};
        TypeColor _lasTypeColor{TypeColor::None};
    };

}