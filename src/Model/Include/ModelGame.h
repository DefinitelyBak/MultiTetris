#pragma once

#include "Precompile.h" 

#include "Map.h"
#include "Factory/ShapeFactory.h"

#include <boost/signals2.hpp>


namespace Tetris::Model
{

    struct DescriptionMap
    {
        DescriptionMap(DataMap _map, MapSize _size, int _score): map(_map), size(_size), score(_score){};

        DataMap map;
        MapSize size;
        int score;
    };

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
        boost::signals2::signal<void(DescriptionMap)> SignalUpdateView; 

    private:
        /// @brief 
        /// @param lines 
        void AddScore(unsigned int lines);

        /// @brief Создание случайного блока
        /// @return Новый блок
        std::shared_ptr<AbstractBlock> CreateRandomBlock(); 

        Map _map;
        Blocks::ShapeFactory _factory;

        unsigned int _score{0};

        IdShape _lastTypeBlock{IdShape::None};
        TypeColor _lasTypeColor{TypeColor::None};

        std::random_device _device;
        std::mt19937 _randomEngine;
    };

}