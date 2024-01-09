#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>
#include <array>

enum class Command {
	Left,
	Up,
	Right,
	Down
};

/// <summary>
/// ����� - ������, ���������:
/// 1) ��������
/// 2) �������� �����
/// 3) 
/// 
/// �������� ������ ������ ��������������: Rotate � ��������� _ofcet.
/// </summary>
class AbstractShape
{
public:
	enum class Stage {
		First,
		Second,
		Third,
		Fourth 
	};
	
	/// <summary>
	/// �����������, ��������� ��������� ��������� ������.
	/// </summary>
	AbstractShape();
	virtual ~AbstractShape(){};

	/// <summary>
	/// �������������� ������, ����� ���� � ���������� ������ ������ �� �����.
	/// </summary>
	/// <returns></returns>
	virtual void init(sf::Color color, sf::Vector2i center);

	virtual void move(Command cm);
	virtual std::array<sf::Vector2i, 4> getCoordinates();
	virtual std::array<sf::Vector2i, 4> getCoordinatesNextStage();

	virtual sf::Color getColor() const { return _color; };
private:
	void changeStage();
protected:
	virtual std::array<sf::Vector2i, 4> getOffset(Stage) = 0;
private:
	sf::Color _color;
protected:
	sf::Vector2i _center;

	Stage _stage;
	Stage _nextStage;
};

