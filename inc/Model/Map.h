#pragma once

#include "AbstractShape.h"

#include "SFML/System/Vector2.hpp"

/// <summary>
/// ����� ����������� ������ ���� �������� ������������,
/// _map - ������ ���� �����.
/// ������ ����� ��������� ������ �����, ���������� ������ � �����,
/// �������� ����� ��������� ������ �� ��������� ���� ��� ���.
/// </summary>
class Map
{
public:
	/// <summary>
	/// ���������� �����.
	/// </summary>
	/// <param name="width">���-�� ������ �� ������</param>
	/// <param name="hight">���-�� ������ �� ������</param>
	Map(int width, int hight);
	~Map();

	void addShape(std::array<sf::Vector2i, 4> coordsShape, sf::Color color);

	void updateMap(std::array<sf::Vector2i, 4> coordsShape);
	bool checkPosition(std::array<sf::Vector2i, 4> newCoords);
	int  checkTetris();

	const int* getMap();
private:
	bool cheakLine(int y);
private:
	std::array<sf::Vector2i, 4> _position; // ������� ��������� ������
	
	int _colorShape; // ���� ���������� ������

	int _width; // ���-�� ������ �� ������
	int _hight; // ���-�� ������ �� ������

	int* _map; // �����
};