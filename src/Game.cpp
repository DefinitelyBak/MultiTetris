#include "Game.h"

Game::Game():
	view(sf::VideoMode(400,600), "Tetris", sf::Style::Titlebar),
	model(Size(20,40))
{
    view.Init(model.GetConfig());
    model.AddView(&view);

    controller.Init(&model, &view);
}

void Game::Run()
{
    controller.Start();

    while (view.IsOpen())
    {
        controller.Update();
    }
}
