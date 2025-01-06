#pragma once

#include <Model/Precompile.h>
#include <Model/Export.h>
#include <Model/Forwards.h>

#include <Model/Types.h>
#include <Model/Blocks/AbstractBlock.h>


namespace Tetris::Model
{
    /// @brief Класс реализации карты для игры Тетрис
    class MODEL_EXPORT Map
    {
    public:
        /// @brief Конструктор по умолчанию, инициализирует пустую карту
        /// @param columns Количество столбцов карты
        /// @param rows Количество строк карты
        Map(size_t columns = 10, size_t rows = 25);

        /// @brief Получить текущую карту
        /// @return Текущая карта
        [[nodiscard]] std::vector<TypeColor> GetMap() const;

        /// @brief Получить размер карты
        /// @return Размер карты
        [[nodiscard]] MapSize GetSize() const;

        /// @brief Проверить, заполнена ли карта
        /// @return True, если карта заполнена, иначе false
        [[nodiscard]] bool IsFull();

        /// @brief Перезапустить карту, очищая её
        void Restart();

        /// @brief Установить активный блок на карту
        /// @param block Указатель на блок
        void SetBlock(AbstractBlockPtr block);

        /// @brief Проверить, имеется ли активный блок
        /// @return True, если активный блок присутствует, иначе false
        [[nodiscard]] bool HasActiveBlock() const;

        /// @brief Переместить активный блок на карте
        /// @param cmn Команда для перемещения
        void MoveBlock(Command cmn);

        /// @brief Получить количество удаленных линий
        /// @return Количество удаленных линий
        [[nodiscard]] unsigned int GetCountDeletedLines() const;

    private:
        /// @brief Удалить заполненные линии из карты
        void DeleteLines();

        /// @brief Проверить, можно ли установить блок в указанное положение
        /// @param pos Положение блока
        /// @return True, если блок может быть установлен, иначе false
        [[nodiscard]] bool IsBlockCanMove(Positions pos);

        /// @brief Установить блок на карту
        /// @param map Ссылка на карту, на которую будет установлен блок
        /// @param size Размер карты
        void SetBlockOnMap(std::vector<TypeColor>& map, MapSize size) const;

        /// @brief Повернуть блок
        /// @param cmn Команда
        void RotateBlock(Command cmn);

        /// @brief плоскопараллельное движение на карте 
        /// @param cmn Команда
        void PlaneParallelMotion(Command cmn);

        /// @brief Получить поле
        /// @param map Карта
        /// @param size Размер карты
        /// @param pos Положение поля
        /// @return Значение поля
        [[nodiscard]] static TypeColor& GetField(std::vector<TypeColor>& map, MapSize size, const Position& pos);

    private:
        AbstractBlockPtr _activeBlock{nullptr}; ///< Указатель на активный блок
        Position _positionBlock{0,0}; ///< Положение активного блока
        std::vector<TypeColor> _data; ///< Данные карты
        MapSize _size{0,0}; ///< Размер карты
        unsigned int _deletedLine{0}; ///< Количество удаленных линий
    };
} // namespace Tetris::Model