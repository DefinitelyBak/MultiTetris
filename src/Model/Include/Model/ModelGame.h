#pragma once

#include <Model/Precompile.h>
#include <Model/Export.h>
#include <Model/Forwards.h>

#include <Model/Types.h>
#include <Model/AbstractModel.h>
#include <Model/Map.h>
#include <Model/Factory/BlocksFactory.h>


namespace Tetris::Model
{
    /// @brief Модель игры Тетрис
    /// 
    /// Этот класс отвечает за управление состоянием игры Тетрис, включая
    /// создание блоков, обновление счета и обработку команд игрока.
    class MODEL_EXPORT ModelGame final : public AbstractModel
    {
    public:
        /// @brief Конструктор по умолчанию
        /// 
        /// Инициализирует игровую модель, создавая карту и регистрируя доступные блоки.
        ModelGame();

    protected:
        /// @brief Обновление модели в ответ на команду
        /// 
        /// Обрабатывает входящие команды, обновляет состояние игры и
        /// передает текущее состояние модели в описание.
        /// 
        /// @param command Команда для обновления модели
        /// @return Снимок модели 
        [[nodiscard]] MementoModelPtr UpdateModel(Command command) override;

    private:
        /// @brief Создание случайного блока
        /// 
        /// Генерирует новый блок случайного типа и цвета. Если указан
        /// блок, он будет исключен из выбора.
        /// 
        /// @param withoutBlock Указатель на блок, который следует исключить
        /// @return Указатель на новый блок
        [[nodiscard]] AbstractBlockPtr CreateRandomBlock(AbstractBlockPtr withoutBlock = nullptr);

        /// @brief Регистрация доступных блоков
        /// 
        /// Добавляет все доступные типы блоков в фабрику блоков для
        /// дальнейшего использования в игре.
        void RegisterBlocks();

        /// @brief Сброс игры
        /// 
        /// Обнуляет состояние игры, включая карту и счет, и
        /// обновляет описание модели.
        void ResetGame();

        /// @brief Обновление счета
        /// 
        /// Проверяет и обновляет счет, если были удалены линии,
        /// и обновляет описание модели.
        void UpdateScore();

        /// @brief Спавн нового блока
        /// 
        /// Создает новый активный блок и обновляет описание модели
        /// для отображения следующего блока.
        void SpawnNewBlock();

        /// @brief Создать снимок модели
        /// @return Снимок модели
        [[nodiscard]] MementoModelPtr MakeMementoModel();

    private:
        Map _map; //< Карта игры, представляющая игровое поле
        Blocks::BlocksFactory _factory; //< Фабрика блоков для создания игровых блоков

        unsigned int _score{0}; //< Текущий счет игрока

        std::random_device _device; //< Генератор случайных чисел для выбора блоков
        std::mt19937 _randomEngine; //< Двигатель случайных чисел для генерации случайных значений

        AbstractBlockPtr _currentBlock; //< Текущий активный блок, который управляется игроком
        AbstractBlockPtr _nextBlock; //< Следующий блок, который будет использоваться в игре
    };
} // namespace Tetris::Model