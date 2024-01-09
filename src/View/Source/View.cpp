#include "View/View.h"

View::View( sf::VideoMode mode, 
		    const sf::String& title, 
		    sf::Uint32 style) :
                _window(mode, title, style),
                _vmap(Size(mode.width, mode.height))
{}

void View::Update()
{
    _vmap.Update();

    _window.clear();
    _window.draw(_vmap);
    _window.display();
}

void View::Init(DiscreptionModel conf)
{
    _vmap.Init(conf);
}

bool View::IsOpen() const
{
    return _window.isOpen();
}

sf::RenderWindow& View::GetWindow()
{
    return _window;
}
