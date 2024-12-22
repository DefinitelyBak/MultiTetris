#pragma once

#include "Precompile.h"
#include "Forwards.h"
#include "Types.h"

#include "Qt/Map.h"


namespace Tetris::View::Qt
{

    // Класс PreviewBlock представляет собой блок предварительного просмотра в игре Тетрис.
    class PreviewBlock final : public Map
    {
        Q_OBJECT  // Макрос Qt для включения мета-объектной системы.
    public:
        // Конструктор класса PreviewBlock.
        // parent - родительское окно, по умолчанию nullptr.
        // withBorder - флаг, указывающий, нужно ли отображать границу блока.
        PreviewBlock(QWindow* parent = nullptr, bool withBorder = false);

        // Устанавливает блок для предварительного просмотра.
        // block - указатель на блок, который нужно установить.
        void SetBlock(const AbstractBlockPtr block);

        // Возвращает тип блока.
        Model::TypeBlock GetType() const;

    private:
        // Переменная для хранения типа формы блока.
        Model::TypeBlock _typeShape{Model::TypeBlock::None}; //< Тип блока.
        
        // Переменная для хранения цвета блока.
        Model::TypeColor _typeColor{Model::TypeColor::None}; //< Цвет блока.
    };
}