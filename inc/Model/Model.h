#pragma once

#include "AbstractShape.h"
#include "Map.h"
#include "AbstratView.h"
#include "ShapeFactory.h"
#include "ConfigModel.h"

#include <SFML/System/Clock.hpp>

#include <queue>
#include <list>

/// <summary>
/// ���� - ��� ���� � ������(�).
/// 
/// ������� ����� ������ ����, ��������:
/// 1) �� ��������������� ������ ����� � �������� ������,
/// 2) ��������� ��������� ������, 
/// </summary>
class Model
{
public:
	Model(int sizeQueue, sf::Vector2i sizeMap);

	void update(Command cm);

	void addView(AbstratView* view);

	ConfigModel getConfig();
private:
	IdShape randomIdShape();
	sf::Color randomColor();

	AbstractShape* createShape();
	void updateViews();
private:
	std::list<AbstratView*> _views;
	Map _map;

	ShapeFactory _factory;

	AbstractShape* _actualShape;
	sf::Vector2i _sizeMap;
};