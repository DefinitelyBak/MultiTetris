#pragma once

#include "Precompile.h"

#include "Forwards.h"
#include "Types.h"

#include "blocks/AbstractBlock.h"


namespace Tetris::Model
{
    /// @brief Класс реализации карты для игры Тетрис
    class Map
    {
    public:
        /// @brief Конструктор по умолчанию, инициализирует пустую карту
        /// @param columns Количество столбцов карты
        /// @param rows Количество строк карты
        Map(size_t columns = 10, size_t rows = 25);

        /// @brief Получить текущую карту
        /// @return Текущая карта
        std::vector<TypeColor> GetMap();

        /// @brief Получить размер карты
        /// @return Размер карты в виде MapSize
        MapSize GetSize() const;

        /// @brief Проверить, заполнена ли карта
        /// @return True, если карта заполнена, иначе false
        bool IsFullMap();

        /// @brief Перезапустить карту, очищая её
        void Restart();

        /// @brief Установить активный блок на карту
        /// @param block Указатель на блок
        void SetBlock(AbstractBlockPtr block);

        /// @brief Проверить, имеется ли активный блок
        /// @return True, если активный блок присутствует, иначе false
        bool HasActiveBlock() const;

        /// @brief Переместить активный блок на карте
        /// @param cmn Команда для перемещения
        void MoveBlock(Command cmn);

        /// @brief Получить количество удаленных линий
        /// @return Количество удаленных линий
        unsigned int GetCountDeletedLines() const;

    private:
        /// @brief Удалить заполненные линии из карты
        void DeleteLines();

        /// @brief Проверить, можно ли установить блок в указанное положение
        /// @param pos Положение блока
        /// @return True, если блок может быть установлен, иначе false
        bool IsBlockCanMove(Positions pos);

        /// @brief Установить блок на карту
        /// @param map Ссылка на карту, на которую будет установлен блок
        void SetBlockOnMap(std::vector<TypeColor>& map);

        /// @brief Повернуть блок
        /// @param cmd Команда
        void RotateBlock(Command cmd);

        /// @brief 
        /// @param map 
        /// @param pos 
        /// @return 
        TypeColor& GetField(std::vector<TypeColor>& map, const Position& pos);

        AbstractBlockPtr _activeBlock; ///< Указатель на активный блок
        Position _positionBlock; ///< Положение активного блока
        std::vector<TypeColor> _data; ///< Данные карты
        MapSize _size; ///< Размер карты
        unsigned int _deletedLine{0}; ///< Количество удаленных линий
    };
} // namespace Tetris::Model