#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Node.h"

class MousePointer
{
public:
	MousePointer();
	virtual ~MousePointer();

	void Update(sf::RenderWindow& pWindow);
	

	inline sf::Vector2f getPosition() { return m_position; };
	inline sf::FloatRect getBoundingBox() { return m_rectShape.getGlobalBounds(); };


	sf::RectangleShape m_rectShape;
private:
	sf::Vector2f m_position;
	sf::Vector2f m_boundingBox;

	

};

