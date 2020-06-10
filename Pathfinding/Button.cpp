#include "Button.h"



Button::Button(sf::Vector2f pSize, sf::Vector2f pPosition, std::string pText, int pID, int pTextSize,sf::Color pButtonColor, sf::Color pTextColor, sf::Vector2f pTextOffset)
	: m_ID(pID)
	, m_textOffset(pTextOffset)
	, m_textSize(pTextSize)
	, m_bActive(false)
{

	this->m_rectShape.setSize(pSize);
	this->m_buttonText.setString(pText);
	this->m_ID = pID;
	this->m_rectShape.setOrigin(this->m_rectShape.getSize().x / 2, this->m_rectShape.getSize().y / 2);
	this->m_rectShape.setFillColor(pButtonColor);

	//Set Text Default Settings
	
	this->m_buttonText.setFillColor(pTextColor);
	this->m_buttonText.setCharacterSize(pTextSize);
	this->m_font.loadFromFile("../Fonts/SegoeMarker.ttf");
	this->m_buttonText.setFont(this->m_font);
	
	
	SetPosition(pPosition);
}


Button::~Button()
{
}

void Button::SetActive(bool pActive)
{
	if (pActive)
	{
		this->m_rectShape.setOutlineThickness(10);
		this->m_bActive = true;
	}
	else
	{
		this->m_rectShape.setOutlineThickness(0);
		this->m_bActive = false;
	}
	
}

void Button::SetPosition(sf::Vector2f pPosition)
{
	this->m_rectShape.setPosition(pPosition);
	this->m_buttonText.setPosition(pPosition + this->m_textOffset); // Apply Text offset
}

void Button::Render(sf::RenderWindow& pWindow)
{
	pWindow.draw(this->m_rectShape);
	pWindow.draw(this->m_buttonText);
}