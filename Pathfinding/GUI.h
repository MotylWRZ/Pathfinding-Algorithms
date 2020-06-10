#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


#include "Button.h"

class MousePointer; // Forward declaration of MousePointer

class GUI
{
public:
	GUI(sf::Vector2f pPosition, sf::Vector2f pSize);
	virtual ~GUI();


	void HandleInput(sf::Mouse::Button pButton, bool pPressed, MousePointer& pMousePointer);
	void Render(sf::RenderWindow& pWindow);
	void AddButton(sf::Vector2f pSize, std::string pText, int pID, int pTextSize = 10,
		sf::Color pButtonColor = sf::Color::White, sf::Color pTextColor = sf::Color::Black,
		sf::Vector2f pTextOffset = sf::Vector2f(0.0f, 0.0f));
	inline void SetActiveButton(Button* pButton) { m_activeButtonPtr = pButton; }; //Point to currently active button
	inline Button* GetActiveButton() { return m_activeButtonPtr; }; // Get a pointer to currently active button

private:
	void UpdatePanel();

	Button* m_Button;
	Button* m_activeButtonPtr; // Pointer to Curently active button
	float m_panelSpace; // Space between the buttons

	sf::RectangleShape m_menuPanel;
	std::vector<Button*> m_vecButtons;


};

