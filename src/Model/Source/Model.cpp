#include <iostream>
/*
void operator+=(std::array<sf::Vector2i, 4>& cor, sf::Vector2i lf);

Model::Model(Size sizeMap) :
	_map(sizeMap)
{
	srand(time(NULL));

	_factory.add<Iblock>(IdShape::Iblock);

	_actualShape = CreateShape();
	_map.SetShape(std::weak_ptr(_actualShape));
}

void Model::Update(Command cm)
{
	DiscreptionShape shapeDisc = _actualShape->GetDescription();

	switch (cm)
	{
	case Command::Left:
		shapeDisc.coordinates += sf::Vector2i(-1, 0);
		break;
	case Command::Right:
		shapeDisc.coordinates += sf::Vector2i(1, 0);
		break;
	case Command::Down:
		shapeDisc.coordinates += sf::Vector2i(0, 1);
		break;
	case Command::Up:
		shapeDisc = _actualShape->GetDescription(true);
		break;
	default:
		break;
	}

	if (_map.CheckPosition(shapeDisc.coordinates))
	{
		_actualShape->Move(cm);
		_map.Update();
	}
	else
	{
		if (cm == Command::Down)
		{
			_actualShape = CreateShape();
			_map.CheckTetris();
			_map.SetShape(std::weak_ptr(_actualShape));
		}
	}

	UpdateViews();
}

void Model::AddView(IView* view)
{
	_views.push_back(view);
}

DiscreptionModel Model::GetConfig()
{
	return _map.GetConfig();
}

IdShape Model::RandomIdShape()
{
	return static_cast<IdShape>(std::rand()%_factory.Size());
}

sf::Color Model::RandomColor()
{
	sf::Color color;
	int i = std::rand() % 7 + 1;
	if (i == 1)
		color = sf::Color::White;
	else if(i == 2)
		color = sf::Color::Red;
	else if (i == 3)
		color = sf::Color::Green;
	else if (i == 4)
		color = sf::Color::Blue;
	else if (i == 5)
		color = sf::Color::Yellow;
	else if (i == 6)
		color = sf::Color::Magenta;
	else if (i == 7)
		color = sf::Color::Cyan;

	return color;
}

std::shared_ptr<AbstractShape> Model::CreateShape()
{
	std::array<sf::Vector2i, 4> center;
	Size sizeMap = _map.GetConfig().size;

	for( auto& x : center) x = sf::Vector2i(sizeMap.width/2, 3);

	DiscreptionShape initShape(RandomColor(), center);

	std::shared_ptr<AbstractShape> shapPtr(_factory.Create(RandomIdShape(), initShape));
	return shapPtr;
}

void Model::UpdateViews()
{
	for (auto& view : _views)
		view->Update();
}

void operator+=(std::array<sf::Vector2i, 4>& cor, sf::Vector2i lf)
{
	for (auto& x : cor) x += lf;
};
*/