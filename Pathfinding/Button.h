#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Button
{
public:
	Button(sf::Vector2f pSize, sf::Vector2f pPosition, std::string pText, int pID);
	virtual ~Button();

	void Render(sf::RenderWindow& pWindow);

	//Accesors/Mutators
	inline sf::Vector2f GetSize() { return m_rectShape.getSize(); };
	inline sf::FloatRect GetBoundingBox() { return m_rectShape.getGlobalBounds(); };
	inline sf::Vector2f GetPosition() { return m_rectShape.getPosition(); };
	inline int GetID() { return m_ID; };

	inline void SetButtonID(int ID) { m_ID = ID; }; //it can be also an enum value
	inline void SetPosition(sf::Vector2f pPosition) { m_rectShape.setPosition(pPosition); };


private:
	sf::RectangleShape m_rectShape;
	sf::Text m_buttonText;
	int m_ID;


};

