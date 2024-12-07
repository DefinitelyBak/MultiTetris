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

        ///@brief Деструктор
        ~ModelGame();

        /// @brief Слот обновление модели игры
        /// @param command Команда для обновления игры
        void SlotUpdate(Command command) override;
        
        /// @brief Добавить отображение модели
        /// @param view отображение
        void SetView(AbstractWidgetPtr view) override;

    private:
        /// @brief 
        /// @param lines 
        void AddScore(unsigned int lines);

        /// @brief Создание случайного блока
        /// @return Новый блок
        AbstractBlockPtr CreateRandomBlock(); 

        boost::signals2::signal<void(Model::DescriptionModel)> SignalUpdateView;

        boost::signals2::signal<void()> SignalCloseViews; 

        Map _map;
        Blocks::BlocksFactory _factory;

        unsigned int _score{0};

        IdShape _lastTypeBlock{IdShape::None};
        TypeColor _lasTypeColor{TypeColor::None};

        std::random_device _device;
        std::mt19937 _randomEngine;

        AbstractBlockPtr _currentBlock;
        AbstractBlockPtr _nextBlock;

        std::mutex _mutex;
    };

}