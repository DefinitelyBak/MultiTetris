#pragma once

#include "Precompile.h"


namespace Tetris::View::SFML
{
    /// @brief Класс Text представляет собой текстовое поле в игре Тетрис.
    /// 
    /// Этот класс наследуется от sf::Text и добавляет дополнительные возможности для работы с текстом.
    class Text final: public sf::Text
    {
    public:
        /// @brief Конструктор класса Text.
        ///
        /// @param fontPath Путь к файлу шрифта.
        /// @param colorText Цвет текста.
        /// @param style Стиль текста.
        Text(const std::string& fontPath, sf::Color colorText, sf::Uint32 style);

    private:
        sf::Font _font; //< Шрифт, используемый для отображения текста
    };
} // namespace Tetris::View::SFML
