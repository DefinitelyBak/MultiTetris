#pragma once

#include <View/Export.h>
#include <View/Precompile.h>
#include <View/Forwards.h>

#include <View/SFML/Map.h>
#include <Model/Types.h>


namespace Tetris::View::SFML
{
    /// @brief Класс WidgetPreviewBlock отвечает за отображение предварительного просмотра блока в игре Тетрис.
    class VIEW_EXPORT WidgetPreviewBlock final: public sf::Drawable, public sf::Transformable
    {
    public:
        ///@brief Конструктор класса.
        ///
        /// @param windowSize Размер окна для отображения блока.
        /// @param withBorder Флаг, указывающий, нужно ли отображать границу.
        WidgetPreviewBlock(const sf::Vector2f& windowSize, bool withBorder = false);

        /// @brief Устанавливает блок для предварительного просмотра.
        /// 
        /// @param block Указатель на блок, который нужно отобразить.
        void SetBlock(const AbstractBlockPtr block);

        ///@brief Возвращает тип текущего блока.
        ///
        ///@return Тип блока.
        Model::TypeBlock GetType() const;

    private:
        /// @brief Переопределение метода draw для рисования блока на целевом объекте.
        /// 
        /// @param target Целевой объект для рисования.
        /// @param states Состояния рисования.
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        Map _map; //< Карта, представляющая блок.

        sf::Vector2f _windowSize; //< Размер окна для отображения блока.

        Model::TypeBlock _typeShape{Model::TypeBlock::None}; //< Тип блока.
        Model::TypeColor _typeColor{Model::TypeColor::None}; //< Цвет блока.
    };
} // namespace Tetris::View::SFML
