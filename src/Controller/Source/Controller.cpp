#include "Controller/Controller.h"

Controller::Controller() :
	_model(nullptr),
	_view(nullptr),
	_interval(sf::seconds(0.05f))
{}

void Controller::Init(Model* ptr_model, View* view)
{
	_model = ptr_model;
	_view = view;
}

void Controller::Start()
{
	_oldTime = _clock.restart();
}


void Controller::Update()
{
	sf::Event event;
	while ((_view->GetWindow()).pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_view->GetWindow().close();
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)))
				_model->Update(Command::Right);
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)))
				_model->Update(Command::Left);
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)))
				_model->Update(Command::Up);
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)))
				_model->Update(Command::Down);
		}
	}

	if (_clock.getElapsedTime() - _oldTime > _interval)
	{
		_model->Update(Command::Down);
		_oldTime = _clock.restart();
	}
}