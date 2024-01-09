#pragma once

#include "data/DiscreptionModel.h"
#include "interfaces/IView.h"
#include "View/ViewMap.h"

#include "SFML/Graphics/RenderWindow.hpp"

class View : public IView
{
public:
	/// @brief 
	/// @param mode  
	/// @param title 
	/// @param style 
	View(sf::VideoMode mode, 
		 const sf::String& title, 
		 sf::Uint32 style = sf::Style::Default);

	/// @brief 
	void Update() override;

	/// @brief 
	/// @param conf 
	void Init(DiscreptionModel conf);

	/// @brief 
	/// @return 
	bool IsOpen() const;

	/// @brief 
	/// @return 
	sf::RenderWindow& GetWindow();
private:
	sf::Vector2f _sizeWindow;

	sf::RenderWindow _window;

	ViewMap _vmap;
};

