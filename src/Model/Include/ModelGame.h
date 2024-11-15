#pragma once

#include "Precompile.h" 

#include "Map.h"
#include "Factory/ShapeFactory.h"

#include <wigwag/signal.hpp>


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

        /// @brief Сигнал на обновление карты
        wigwag::signal<void(DataMap, MapSize, unsigned int)> UpdateView;

    private:
        /// @brief 
        /// @param lines 
        void AddScore(unsigned int lines);

        /// @brief Создание случайного блока
        /// @return Новый блок
        std::unique_ptr<AbstractBlock> CreateRandomBlock(); 

        Map _map;
        Blocks::ShapeFactory _factory;

        unsigned int _score{0};

        IdShape _lastTypeBlock{IdShape::None};
        Color _lasTypeColor{Color::None};

        std::random_device _device;
        std::mt19937 _randomEngine;
    };

}