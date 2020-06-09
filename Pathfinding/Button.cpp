#include "Button.h"



Button::Button(sf::Vector2f pSize, sf::Vector2f pPosition, std::string pText, int pID)
{
	this->m_rectShape.setSize(pSize);
	this->m_rectShape.setPosition(pPosition);
	this->m_buttonText.setString(pText);
	this->m_ID = pID;
	this->m_rectShape.setOrigin(this->m_rectShape.getSize().x / 2, this->m_rectShape.getSize().y / 2);
}


Button::~Button()
{
}


void Button::Render(sf::RenderWindow& pWindow)
{
	pWindow.draw(this->m_rectShape);
	pWindow.draw(this->m_buttonText);
}