#include <View/SFML/Map.h>


namespace Tetris::View::SFML
{
    sf::Color ColorFromTypeColor(Model::TypeColor color)
    {
        switch (color)
        {
        case Model::TypeColor::Blue:
            return sf::Color::Blue;
        case Model::TypeColor::Green:
            return sf::Color::Green;
        case Model::TypeColor::Red:
            return sf::Color::Red;
        case Model::TypeColor::Yellow:
            return sf::Color::Yellow;
        default:
            return sf::Color::Black; // Возврат черного цвета по умолчанию.
        }
    }

    Map::Map(sf::Vector2f windowSize, bool withBorder)
        : _windowSize(windowSize), _rows(0), _columns(0)
    {
        if (withBorder)
            InitializeBorders();
    }

    void Map::InitializeBorders()
    {
        float borderSize = _windowSize.y / 100;
        _borderWidth = borderSize;

        // Создание вертикальных границ.
        _borders.emplace_back(CreateBorder(sf::Vector2f(_borderWidth, _windowSize.y), sf::Vector2f(0, 0)));
        _borders.emplace_back(CreateBorder(sf::Vector2f(_borderWidth, _windowSize.y), sf::Vector2f(_windowSize.x - _borderWidth, 0)));

        // Создание горизонтальных границ.
        _borders.emplace_back(CreateBorder(sf::Vector2f(_windowSize.x, _borderWidth), sf::Vector2f(0, 0)));
        _borders.emplace_back(CreateBorder(sf::Vector2f(_windowSize.x, _borderWidth), sf::Vector2f(0, _windowSize.y - _borderWidth)));
    }

    sf::RectangleShape Map::CreateBorder(const sf::Vector2f& size, const sf::Vector2f& position)
    {
        sf::RectangleShape border(size);
        border.setPosition(position);
        border.setFillColor(sf::Color::White);
        return border;
    }

    void Map::SetMap(const std::vector<Model::TypeColor>& map, const Model::MapSize& size)
    {
        if (map.empty() || size.rows <= 0 || size.columns <= 0)
            return;

        _map = map;

        if (_map.size() != _fields.size())
        {
            _rows = size.rows;
            _columns = size.columns;
            UpdateFieldSizes();
        }

        UpdateView();
    }

    void Map::UpdateFieldSizes()
    {
        _offsetX = (_windowSize.x - 2 * _borderWidth) / _columns;
        _offsetY = (_windowSize.y - 2 * _borderWidth) / _rows;

        _fields.resize(_rows * _columns);
        for (auto& field : _fields)
        {
            field.setSize(sf::Vector2f(_offsetX, _offsetY));
            field.setFillColor(sf::Color::Black);
        }
    }

    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const auto& border : _borders)
            target.draw(border, states);
        
        if (_map.empty() || _fields.empty())
            return;

        for (const auto& field : _fields)
            target.draw(field, states);
    }

    void Map::UpdateView()
    {
        int index = 0;
        for (int row = 0; row < _rows; ++row)
        {
            for (int column = 0; column < _columns; ++column)
            {
                auto color = _map[row * _columns + column];
                _fields[index].setFillColor(ColorFromTypeColor(color));
                sf::Vector2f position{ _borderWidth + column * _offsetX, _windowSize.y - (row + 1) * _offsetY - _borderWidth };
                _fields[index].setPosition(position);
                ++index;
            }
        }
    }
}