#include "MousePointer.h"



MousePointer::MousePointer()
{
	m_rectShape.setSize(sf::Vector2f(0.1, 0.1f));
	m_rectShape.setFillColor(sf::Color::Blue);
}


MousePointer::~MousePointer()
{
}


void MousePointer::Update(sf::RenderWindow& pWindow)
{
	//Set the position to the current position of the mouse in the window
	sf::Vector2i tMousePixelPos = sf::Mouse::getPosition(pWindow);
	sf::Vector2f tMouseWorldPos = pWindow.mapPixelToCoords(tMousePixelPos);

	this->m_position = tMouseWorldPos;
	this->m_rectShape.setPosition(m_position);
}