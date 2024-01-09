/*
#include "model/ModelMap.h"

ModelMap::ModelMap(Size sizeMap):
	_sizeMap(sizeMap),
	_map(size_t(_sizeMap.hight * _sizeMap.width), 0)
{}

void ModelMap::SetShape(std::weak_ptr<AbstractShape> shapePtr)
{
	_actualShapePtr = shapePtr;
	if (_actualShapePtr.expired()) return;

	auto sharedPtr = _actualShapePtr.lock();

	DiscreptionShape discShape = sharedPtr->GetDescription();

	int idColor = GetIdColor(discShape.color);

	_lastCoordinates = sharedPtr->GetDescription().coordinates;
	for (auto& cor : discShape.coordinates) {
		if (cor.x < 0 || cor.x > _sizeMap.width - 1 || cor.y < 0) continue;

		_map[cor.y * _sizeMap.width + cor.x] = idColor;
	}
}


void ModelMap::Update()
{
	for (auto& cor : _lastCoordinates) {
		if (cor.x < 0 || cor.x > _sizeMap.width - 1 || cor.y < 0) continue;

		_map[cor.y * _sizeMap.width + cor.x] = 0;
	}

	if (_actualShapePtr.expired()) return;

	auto sharedPtr = _actualShapePtr.lock();

	DiscreptionShape discShape = sharedPtr->GetDescription();
	int idColor = GetIdColor(discShape.color);

	for (auto& cor : discShape.coordinates) 
	{
		if (cor.x < 0 || cor.x > _sizeMap.width - 1 || cor.y < 0) continue;

		_map[cor.y * _sizeMap.width + cor.x] = idColor;
	}

	_lastCoordinates = discShape.coordinates;
}

bool ModelMap::CheckPosition(std::array<sf::Vector2i, 4> newCoords)
{
	int idColor = _map[_lastCoordinates[0].y * _sizeMap.width + _lastCoordinates[0].x];

	for (auto& cor : _lastCoordinates) {
		if (cor.x < 0 || cor.x > _sizeMap.width - 1 || cor.y < 0) continue;

		_map[cor.y * _sizeMap.width + cor.x] = 0;
	}

	bool state = true;

	for (auto& coor : newCoords) {
		if (coor.x < 0
			|| (coor.x > (_sizeMap.width - 1))
			|| (coor.y > (_sizeMap.width - 1))
			|| (coor.y < 0))
		{
			state = false;
			break;
		}

		if (_map[coor.y * _sizeMap.width + coor.x] != 0) {
			state = false;
			break;
		}
	}
	
	for (auto& cor : _lastCoordinates) {
		if (cor.x < 0 || cor.x > _sizeMap.width - 1 || cor.y < 0) continue;
		_map[cor.y * _sizeMap.width + cor.x] = idColor;
	}
	
	return state;
}

int ModelMap::CheckTetris()
{
	/// _____________
	/// |* * * * * *| 
	/// |1 1 1 1 1 0|
	/// |1 0 1 0 0 0| <--- 
	/// |1 1 1 1 1 1|
	/// |1 1 1 1 1 1| <--- 
	/// `````````````

	int startLine = -1;
	int endLine = -1;
	bool firstOccurrence = false;
	for (int y = _sizeMap.hight - 1; y > 0; y--)
	{
		if (!firstOccurrence)
		{
			if (CheakLine(y))
			{
				firstOccurrence = true;
				startLine = y;
			}
		}
		else if (!CheakLine(y))
			{
				endLine = y;
				break;
			}
	}

	if (startLine == endLine) return 0;

	int gap = startLine - endLine;

	for (int y = endLine; y > 0; y--)
		for (int x = 0; x < _sizeMap.width - 1; x++)
			_map[(y + gap) * _sizeMap.width + x] = _map[y * _sizeMap.width + x];

	
	for (int y = 0; y < gap; y++)
		for (int x = 0; x < _sizeMap.width - 1; x++)
			_map[y * _sizeMap.width + x] = 0;

	return gap;
}

bool ModelMap::CheakLine(int numberLine)
{
	for (int x = 0; x < _sizeMap.width; x++)
		if (_map[numberLine * _sizeMap.width + x] == 0) return false;

	return true;
}
DiscreptionModel ModelMap::GetConfig()
{
    return DiscreptionModel(std::span(_map), _sizeMap);
}

int ModelMap::GetIdColor(sf::Color color)
{
	if (color == sf::Color::White)
		return 1;
	else if (color == sf::Color::Red)
		return 2;
	else if (color == sf::Color::Green)
		return 3;
	else if (color == sf::Color::Blue)
		return 4;
	else if (color == sf::Color::Yellow)
		return 5;
	else if (color == sf::Color::Magenta)
		return 6;
	else if (color == sf::Color::Cyan)
		return 7;
	else
		return 0;
}
*/