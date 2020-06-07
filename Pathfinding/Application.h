#pragma once
#include <SFML/Graphics.hpp>


class Application
{
public:
	Application(int pWindowWidth, int pWindowHeight);
	virtual ~Application();

	void HandleEvent(const sf::Event& pEvent);
	void HandleInput(sf::Mouse::Button pButton, bool pPressed);
	void Update(sf::Time pDeltaTime);
	void Render();

	void Run();


private:
	sf::Event m_event;
	sf::RenderWindow m_window;
	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	sf::Time  m_desiredUpdateTime;

private:

	
};

