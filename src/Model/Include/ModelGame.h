#pragma once

#include "Precompile.h"

#include "Forwards.h"
#include "Types.h"

#include "AbstractModel.h"
#include "Map.h"
#include "Factory/BlocksFactory.h"


namespace Tetris::Model
{
    /// @brief Модель игры Тетрис
    /// 
    /// Этот класс отвечает за управление состоянием игры Тетрис, включая
    /// создание блоков, обновление счета и обработку команд игрока.
    class ModelGame final : public AbstractModel
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
        /// @param desc Описание текущего состояния модели
        void UpdateModel(Command command, DescriptionModel& desc) override;

    private:
        /// @brief Добавление очков за удаленные линии
        /// 
        /// Увеличивает текущий счет игрока на основе количества удаленных линий.
        /// 
        /// @param lines Количество удаленных линий
        void AddScore(unsigned int lines);

        /// @brief Создание случайного блока
        /// 
        /// Генерирует новый блок случайного типа и цвета. Если указан
        /// блок, он будет исключен из выбора.
        /// 
        /// @param withoutBlock Указатель на блок, который следует исключить
        /// @return Указатель на новый блок
        AbstractBlockPtr CreateRandomBlock(AbstractBlockPtr withoutBlock = nullptr);

        /// @brief Создание блока на основе типов и цветов
        /// 
        /// Создает блок, выбирая случайный тип и цвет из переданных массивов.
        /// 
        /// @param blockTypes Массив типов блоков
        /// @param colorTypes Массив цветов блоков
        /// @return Указатель на созданный блок
        AbstractBlockPtr CreateBlock(const std::array<TypeBlock, 7>& blockTypes, const std::array<TypeColor, 4>& colorTypes);

        /// @brief Создание блока, исключая указанный
        /// 
        /// Создает блок, исключая указанный блок из возможных вариантов.
        /// 
        /// @param withoutBlock Указатель на блок, который следует исключить
        /// @param blockTypes Массив типов блоков
        /// @param colorTypes Массив цветов блоков
        /// @return Указатель на созданный блок
        AbstractBlockPtr CreateBlockExcluding(AbstractBlockPtr withoutBlock, const std::array<TypeBlock, 7>& blockTypes, const std::array<TypeColor, 4>& colorTypes);

        /// @brief Заполнение массива, исключая определенное значение
        /// 
        /// Копирует элементы из исходного массива в целевой, пропуская
        /// указанный элемент. Используется для создания массива без
        /// определенных блоков или цветов.
        /// 
        /// @tparam T Тип элементов массива
        /// @tparam N Размер исходного массива
        /// @param source Исходный массив
        /// @param excluded Элемент, который следует исключить
        /// @param dest Целевой массив для заполнения
        template<typename T, size_t N>
        void FillExcludingArray(const std::array<T, N>& source, T excluded, std::array<T, N-1>& dest);

        /// @brief Регистрация доступных блоков
        /// 
        /// Добавляет все доступные типы блоков в фабрику блоков для
        /// дальнейшего использования в игре.
        void RegisterBlocks();

        /// @brief Сброс игры
        /// 
        /// Обнуляет состояние игры, включая карту и счет, и
        /// обновляет описание модели.
        /// 
        /// @param desc Описание текущего состояния модели
        void ResetGame(DescriptionModel &desc);

        /// @brief Обновление счета
        /// 
        /// Проверяет и обновляет счет, если были удалены линии,
        /// и обновляет описание модели.
        /// 
        /// @param desc Описание текущего состояния модели
        void UpdateScore(DescriptionModel &desc);

        /// @brief Спавн нового блока
        /// 
        /// Создает новый активный блок и обновляет описание модели
        /// для отображения следующего блока.
        /// 
        /// @param desc Описание текущего состояния модели
        void SpawnNewBlock(DescriptionModel &desc);

    private:
        Map _map; ///< Карта игры, представляющая игровое поле

        Blocks::BlocksFactory _factory; ///< Фабрика блоков для создания игровых блоков

        unsigned int _score{0}; ///< Текущий счет игрока

        std::random_device _device; ///< Генератор случайных чисел для выбора блоков
        std::mt19937 _randomEngine; ///< Двигатель случайных чисел для генерации случайных значений

        AbstractBlockPtr _currentBlock; ///< Текущий активный блок, который управляется игроком
        AbstractBlockPtr _nextBlock; ///< Следующий блок, который будет использоваться в игре
    };
} // namespace Tetris::Model