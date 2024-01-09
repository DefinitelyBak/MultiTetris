#pragma once

#include "View.h"
#include "Model.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>

#include <cstdlib>

/// <summary>
/// ����� ����������, ��������:
/// 1) �� ��������� ������� ������� ������������
/// 2) ����� ���������� ��������� ������.
/// </summary>
class Controller
{
public:
	Controller();

	void init(Model* ptr_model, View* view);
	void start();
	void update();

private:
	Model* _model; // ������ � ������� ��������� ��������������.
	View* _view;
	sf::Clock _clock; //

	sf::Time _interval;
	sf::Time _oldTime;
};

