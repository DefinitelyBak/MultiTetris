#include "SFMLMap.h"

#include "SFML/Graphics/RenderTarget.hpp"


namespace Tetris::View
{
    sf::Color ColorFromTypeColor(Model::TypeColor color)
    {
        switch (color)
        {
        case Model::TypeColor::Blue :
            return sf::Color::Blue;
        case Model::TypeColor::Green :
            return sf::Color::Green;
        case Model::TypeColor::Red :
            return sf::Color::Red;
        case Model::TypeColor::Yellow :
            return sf::Color::Yellow;
        default:
            break;
        }
        return sf::Color::Black;
    }

    SFMLMap::SFMLMap(sf::Vector2f windowSize, bool withBorder):_windowSize(windowSize), _rows(0), _columns(0)
    {
        if(withBorder)
        {
            // Граница будет 0.01 от ширины или высоты.  
            float borderY = windowSize.y/100;
            float borderX = windowSize.y/100;

            _borderWidth = std::max(borderY, borderX);

            /// Вертикальные границы
            sf::RectangleShape border(sf::RectangleShape(sf::Vector2f(_borderWidth, windowSize.y)));
            border.setPosition(sf::Vector2f(0, 0));
            border.setFillColor(sf::Color::White);
            _borders.push_back(border);

            border = sf::RectangleShape(sf::Vector2f(_borderWidth, windowSize.y));
            border.setPosition(sf::Vector2f(windowSize.x - _borderWidth, 0));
            border.setFillColor(sf::Color::White);
            _borders.push_back(border);
            
            /// Горизонтальные линии
            border = sf::RectangleShape(sf::Vector2f(windowSize.x, _borderWidth));
            border.setPosition(sf::Vector2f(0, 0));
            border.setFillColor(sf::Color::White);
            _borders.push_back(border);

            border = sf::RectangleShape(sf::Vector2f(windowSize.x, _borderWidth));
            border.setPosition(sf::Vector2f(0, windowSize.y - _borderWidth));
            border.setFillColor(sf::Color::White);
            _borders.push_back(border);
        }
    }

    void SFMLMap::SetMap(Model::DataMap map, int rows, int columns)
    {
        // Проверка на дурака
        if(map.empty() || rows == 0 || columns == 0 || map.size() != rows* columns)
            return;

        _map = map;
        // Если несовподает размер текущей карты с кол-во фигур
        if(_map.size() != _filds.size())
        {
            _rows = rows;
            _columns = columns;

            _offsetX = (_windowSize.x - 2*_borderWidth)/_columns;
            _offsetY = (_windowSize.y - 2*_borderWidth)/_rows;

            _filds.resize(_map.size());
            for(auto& fild: _filds)
            {
                fild.setSize(sf::Vector2f(_offsetX, _offsetY));
                fild.setFillColor(sf::Color::Black);
            }
        }

        UpdateView();
    }

    void SFMLMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        if (!_borders.empty())
        {
            for(const auto& border: _borders)
                target.draw(border, states);
        }

        if(_map.empty() || _filds.empty())
            return;

        for(const auto& fild: _filds)
            target.draw(fild, states);
    }

    void SFMLMap::UpdateView()
    {
        int i = 0;
        for(int row = 0; row < _rows; ++row)
        {
            for(int column = 0; column < _columns; ++column)
            {
                auto color = _map[row * _columns + column];
                _filds[i].setFillColor(ColorFromTypeColor(color));
                _filds[i].setPosition(_borderWidth + column * _offsetX,  _windowSize.y - row * _offsetY - _offsetY - _borderWidth);
                ++i;
            }
        } 
    }
}