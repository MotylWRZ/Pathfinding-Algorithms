#pragma once
#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "MousePointer.h"
#include "Pathfinder.h"
#include "GUI.h"
#include "AppStructures.h"



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


	MousePointer m_mousePointer;
	Grid m_grid;

	//Create a pathfinder
	Pathfinder m_PathFinder;
	GUI* m_nodesPanel;
	GUI* m_algorithmsPanel;

	E_PATHDINDER_METHOD m_eCurrentMethod;
	E_ACTIVE_NODE m_eCurrentNode;

	bool m_leftMouseBtnPressed;
	
};

