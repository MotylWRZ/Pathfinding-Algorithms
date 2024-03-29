#include "GUI.h"
#include "MousePointer.h"



GUI::GUI(sf::Vector2f pPosition, sf::Vector2f pSize)
	: m_panelSpace(10)
	, m_activeButtonPtr(nullptr)
{
	
	this->m_menuPanel.setSize(pSize);
	this->m_menuPanel.setFillColor(sf::Color(128, 128, 128));
	this->m_menuPanel.setOutlineColor(sf::Color(119, 136, 153));
	this->m_menuPanel.setOutlineThickness(10);
	this->m_menuPanel.setPosition(pPosition);

}


GUI::~GUI()
{
	// Clear the memory from button instances
	for (int i = 0; i < m_vecButtons.size(); i++)
	{
		Button* tPtr = m_vecButtons[i];
		m_vecButtons.erase(m_vecButtons.begin() + i);
		delete tPtr;
	}
}

Button* GUI::GetButtonWithID(int pID)
{
	for (auto tBtn : this->m_vecButtons)
	{
		if (tBtn->GetID() == pID)
		{
			return tBtn;
			break;
		}
	}
}

void GUI::AddButton(sf::Vector2f pSize, std::string pText, int pID, int pTextSize, sf::Color pButtonColor, sf::Color pTextColor, sf::Vector2f pTextOffset, bool pIsClickable)
{
	//Create a button
	Button* tButton = new Button(pSize, sf::Vector2f(50.0f, 100.0f), pText, pID, pTextSize, pButtonColor, pTextColor, pTextOffset, pIsClickable);
	this->m_vecButtons.push_back(tButton);

	// Update the panel and position all buttons
	UpdatePanel();

}

void GUI::HandleInput(sf::Mouse::Button pButton, bool pPressed, MousePointer& pMousePointer)
{
	switch (pButton)
	{
	case sf::Mouse::Left:
	{
		for (auto& tButton : this->m_vecButtons)
		{
			// Do nothing with this button if it is not clickable
			if (!tButton->IsButtonClickable())
				return;

			if (tButton->GetBoundingBox().intersects(pMousePointer.getBoundingBox()))
			{
				// Set all active buttons to inactive
				for (auto& tButton : this->m_vecButtons)
				{
					if (tButton->IsButtonActive())
					{
						tButton->SetActive(false);
					}
				}
				//Activate clicked button
				tButton->SetActive(true);
				// Set clicked button as currently active button
				SetActiveButton(tButton);
			}
		}
		break;
	}
	}
}

void GUI::SetAllButtonsAsInactive()
{
	//Deactivate All buttons
	for (auto& tButton : this->m_vecButtons)
	{
		tButton->SetActive(false);
	}

	// Set pointer to current button as a nullptr
	if (GetActiveButton() != nullptr)
	{
		m_activeButtonPtr = nullptr;
	}
	
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
	// Render all GUI elements
	pWindow.draw(this->m_menuPanel);
	
	for (auto tButton : this->m_vecButtons)
	{
		tButton->Render(pWindow);
	}

}
