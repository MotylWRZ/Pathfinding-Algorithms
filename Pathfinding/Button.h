#pragma once
#include <SFML/Graphics.hpp>

#include <string>
class Button
{
public:
	Button(sf::Vector2f pSize, sf::Vector2f pPosition, std::string pText, int pID, int pTextSize, sf::Color pButtonColor, sf::Color pTextColor, sf::Vector2f pTextOffset, bool m_IsClickable = true);
	virtual ~Button();

	
	void Render(sf::RenderWindow& pWindow);

	//Accesors/Mutators
	inline sf::Vector2f GetSize() { return m_rectShape.getSize(); };
	inline sf::FloatRect GetBoundingBox() { return m_rectShape.getGlobalBounds(); };
	inline sf::Vector2f GetPosition() { return m_rectShape.getPosition(); };
	inline int GetID() { return m_ID; };
	inline bool IsButtonActive() { return m_bActive; };
	inline bool IsButtonClickable() { return m_bIsClickable; };

	inline void SetButtonID(int ID) { m_ID = ID; }; //it can be also an enum value
	void SetPosition(sf::Vector2f pPosition);
	void SetActive(bool pActive);
	inline void SetIsClickable(bool pIsClickable) { m_bIsClickable = pIsClickable; };
	inline void SetText(std::string pText) { m_buttonText.setString(pText); };
	
private:
	sf::RectangleShape m_rectShape;
	sf::Text m_buttonText;
	sf::Vector2f m_textOffset;
	int m_textSize;
	int m_ID;
	sf::Font m_font;
	
	bool m_bActive;
	bool m_bIsClickable;

};

