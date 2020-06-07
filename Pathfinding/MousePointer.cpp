#include "MousePointer.h"



MousePointer::MousePointer()
{
	m_rectShape.setSize(sf::Vector2f(0.1, 0.1f));
	m_rectShape.setFillColor(sf::Color::Blue);
}


MousePointer::~MousePointer()
{
}

void MousePointer::Initialise(sf::RenderWindow& pWindow)
{
	SetCurrentWindow(pWindow);
}


void MousePointer::Update()
{
	//Set the position to the current position of the mouse in the window
	sf::Vector2i tMousePixelPos = sf::Mouse::getPosition(*m_currentWindowPtr);
	sf::Vector2f tMouseWorldPos = m_currentWindowPtr->mapPixelToCoords(tMousePixelPos);

	this->m_position = tMouseWorldPos;
	this->m_rectShape.setPosition(m_position);
}


void MousePointer::SetCurrentWindow(sf::RenderWindow& pWindow)
{
	this->m_currentWindowPtr = &pWindow;
}