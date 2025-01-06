#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <Model/Types.h>
#include <View/Qt/Map.h>


namespace Tetris::View::Qt
{

    /// @brief Класс WidgetPreviewBlock представляет собой блок предварительного просмотра в игре Тетрис.
    class VIEW_EXPORT WidgetPreviewBlock final : public Map
    {
        Q_OBJECT
    public:
        /// @brief Конструктор класса PreviewBlock.
        /// @param parent - родительское окно, по умолчанию nullptr.
        WidgetPreviewBlock(QWidget* parent = nullptr);

        /// @brief Устанавливает блок для предварительного просмотра.
        /// @param block - указатель на блок, который нужно установить.
        void SetBlock(const AbstractBlockPtr block);

        /// @brief Возвращает тип блока.
        [[nodiscard]] Model::TypeBlock GetType() const;

    private:
        Model::TypeBlock _typeShape{Model::TypeBlock::None}; //< Тип блока.
        Model::TypeColor _typeColor{Model::TypeColor::None}; //< Цвет блока.
    };
}