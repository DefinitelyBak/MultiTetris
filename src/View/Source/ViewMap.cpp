#include "View/ViewMap.h"

ViewMap::ViewMap(Size sizeWindow)
{
    _sizeWindow = sizeWindow;
}

void ViewMap::Init(DiscreptionModel disc)
{
    _sizeMap = disc.size;
    _map = disc.map;

    _vertices.setPrimitiveType(sf::Triangles);
    _vertices.resize(_sizeMap.width * _sizeMap.hight * 6);

    _tileSize.x = _sizeWindow.width / _sizeMap.width;
    _tileSize.y = _sizeWindow.hight / _sizeMap.hight;
}

void ViewMap::Update()
{
    if (_map.empty()) return;
    
    int x = 0, y = 0;

    for (size_t count = 0; count < size_t(_sizeMap.width * _sizeMap.hight); ++count)
    {
        sf::Color color = GetColorTitle(_map[count]);
        CreateTitle(x, y, color);

        (x < _sizeMap.width - 1) ? x++ : x = 0, y++;
    }
}


void ViewMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_vertices, states);
}

void ViewMap::CreateTitle(int x, int y, sf::Color color)
{
    sf::Vertex* triangles = &_vertices[(x + y * _sizeMap.width) * 6];

    triangles[0].position = sf::Vector2f(x * _tileSize.x, y * _tileSize.y);
    triangles[1].position = sf::Vector2f((x + 1) * _tileSize.x, y * _tileSize.y);
    triangles[2].position = sf::Vector2f(x * _tileSize.x, (y + 1) * _tileSize.y);
    triangles[3].position = sf::Vector2f(x * _tileSize.x, (y + 1) * _tileSize.y);
    triangles[4].position = sf::Vector2f((x + 1) * _tileSize.x, y * _tileSize.y);
    triangles[5].position = sf::Vector2f((x + 1) * _tileSize.x, (y + 1) * _tileSize.y);

    for (int i = 0; i < 6; i++) 
        triangles[i].color = color;
}

sf::Color ViewMap::GetColorTitle(int codetitle)
{
    switch (codetitle)
    {
    case 0:
        return sf::Color::Black;
    case 1:
        return sf::Color::White;
    case 2:
        return sf::Color::Red;
    case 3:
        return sf::Color::Green;
    case 4:
        return sf::Color::Blue;
    case 5:
        return sf::Color::Yellow;
    case 6:
        return sf::Color::Magenta;
    case 7:
        return sf::Color::Cyan;
    default:
        return sf::Color::Black;
    }
}
