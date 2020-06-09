#include "GUI.h"



GUI::GUI(sf::Vector2f pPosition)
	: m_panelSpace(10)
{
	


	
	this->m_menuPanel.setSize(sf::Vector2f(300.0f, 500.0f));
	//this->m_menuPanel.setOrigin(sf::Vector2f(m_menuPanel.getSize().x / 2, m_menuPanel.getSize().y / 2));
	this->m_menuPanel.setFillColor(sf::Color(128, 128, 128));
	this->m_menuPanel.setOutlineColor(sf::Color(119, 136, 153));
	this->m_menuPanel.setOutlineThickness(10);
	this->m_menuPanel.setPosition(pPosition);



}


GUI::~GUI()
{
}



void GUI::AddButton(sf::Vector2f pSize, std::string pText, int pID)
{
	//Create a button
	Button* tButton = new Button(pSize, sf::Vector2f(50.0f, 100.0f), pText, pID);
	this->m_vecButtons.push_back(tButton);

	// Update the panel and position all buttons
	UpdatePanel();

}

void GUI::UpdatePanel()
{
	sf::Vector2f tPos(this->m_menuPanel.getPosition().x + this->m_menuPanel.getSize().x / 2, 
		              this->m_menuPanel.getPosition().y + this->m_panelSpace);
	//Position the buttons
	for (auto tButton : this->m_vecButtons)
	{
		tButton->SetPosition(sf::Vector2f(tPos.x, tPos.y + tButton->GetSize().y));
		
		tPos.y += this->m_panelSpace + tButton->GetSize().y;
	}

}

void GUI::Render(sf::RenderWindow& pWindow)
{
	pWindow.draw(this->m_menuPanel);
	
	for (auto tButton : this->m_vecButtons)
	{
		tButton->Render(pWindow);
	}

}
