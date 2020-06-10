#include "Application.h"
#include <cstdlib>

#include <string>
#include <algorithm>
#include <iostream>
#include <list>





Application::Application(int pWindowWidth, int pWindowHeight)
	: m_window(sf::VideoMode(pWindowWidth, pWindowHeight), "PathfindingApplication")
	, m_screenWidth(pWindowWidth)
	, m_screenHeight(pWindowHeight)
	, m_desiredUpdateTime(sf::seconds(1.0f / 60.0f))
	, m_eCurrentMethod(E_PATHDINDER_METHOD::E_NONE)
	, m_leftMouseBtnPressed(false)
	

{
	//Initialise Mouse Pointer
	this->m_mousePointer.Initialise(this->m_window);

	//Create a grid of nodes
	this->m_grid.createGrid(sf::Vector2f(100.0f, 100.0f), 20, 20, sf::Vector2f(20.0f, 20.0f), 1.0f);

	//Create GUI
	this->m_nodesPanel = new GUI(sf::Vector2f(700.0f, 110.0f), sf::Vector2f(170.0f, 270.0f));
	this->m_nodesPanel->AddButton(sf::Vector2f(100.0f, 50.0f), "Set Start", E_ACTIVE_NODE::E_NODE_START, 20, sf::Color::Green, sf::Color::White, sf::Vector2f(-30.0f, -10.0f));
	this->m_nodesPanel->AddButton(sf::Vector2f(100.0f, 50.0f), "Set End", E_ACTIVE_NODE::E_NODE_END, 20, sf::Color::Red, sf::Color::White, sf::Vector2f(-30.0f, -10.0f));
	this->m_nodesPanel->AddButton(sf::Vector2f(100.0f, 50.0f), "Set Obstacle", E_ACTIVE_NODE::E_NODE_OBSTACLE, 20, sf::Color::Magenta, sf::Color::White, sf::Vector2f(-40.0f, -10.0f));
	this->m_nodesPanel->AddButton(sf::Vector2f(100.0f, 50.0f), "Remove Obstacle", E_ACTIVE_NODE::E_NODE_NO_OBSTACLE, 15, sf::Color::White, sf::Color::Black, sf::Vector2f(-40.0f, -10.0f));

	this->m_algorithmsPanel = new GUI(sf::Vector2f(900.0f, 110.0f), sf::Vector2f(170.0f, 270.0f));
	this->m_algorithmsPanel->AddButton(sf::Vector2f(100.0f, 50.0f), "Solve A*", E_PATHDINDER_METHOD::E_ASTAR, 20, sf::Color::Black, sf::Color::White, sf::Vector2f(-30.0f, -10.0f));
	this->m_algorithmsPanel->AddButton(sf::Vector2f(100.0f, 50.0f), "Solve Dijkstra", E_PATHDINDER_METHOD::E_DIJKSTRA, 20, sf::Color::Black, sf::Color::White, sf::Vector2f(-50.0f, -10.0f));


	
}


Application::~Application()
{
	delete this->m_nodesPanel;
	delete this->m_algorithmsPanel;
}

void Application::Update(sf::Time pDeltaTime)
{
	this->m_mousePointer.Update();

	// Check whether the left button is still pressed. If it is, perform the node drawing
	if (this->m_leftMouseBtnPressed)
	{
		this->m_grid.DrawNodes(this->m_eCurrentNode, this->m_mousePointer);
	}
}

void Application::Render()
{

	m_window.clear();

	// Render all nodes
	for (auto& tNode : m_grid.m_vecNodes)
	{
		this->m_window.draw(tNode.m_rectShape);
	}

	this->m_window.draw(this->m_mousePointer.m_rectShape);
	//Render GUI
	this->m_nodesPanel->Render(this->m_window);
	this->m_algorithmsPanel->Render(this->m_window);

	m_window.display();
}


void Application::Run()
{

	sf::Clock clock;

	//Variable to ttrack the time since update() was last executed
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (this->m_window.isOpen())
	{
		//Allows to close tyhe wondow using X button (window can also be reallocated using mouse)
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_window.close();


			//Switch on event function
			HandleEvent(event);

		}

		//get the elapsed time since the last loop
		sf::Time tDeltaTime = clock.restart();

		timeSinceLastUpdate += tDeltaTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			Update(m_desiredUpdateTime);

			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		//Render results to the screen
		Render();

	}
}



void Application::HandleEvent(const sf::Event& pEvent)
{
	//Cache the passed event locally
	sf::Event tEvent = pEvent;

	//Switch statement to decide between the different event types
	switch (tEvent.type)
	{
	case sf::Event::MouseButtonPressed:
	{
	
		// Handle GUI Events
		this->m_nodesPanel->HandleInput(tEvent.mouseButton.button, true, this->m_mousePointer);
		//get current active Node and assign the value to ECurrentNode enum (if active button is NOT a nullptr)
		if (this->m_nodesPanel->GetActiveButton())
		{
			this->m_eCurrentNode = static_cast<E_ACTIVE_NODE>(this->m_nodesPanel->GetActiveButton()->GetID());
		}
		this->m_algorithmsPanel->HandleInput(tEvent.mouseButton.button, true, this->m_mousePointer);
		//Get current active Pathfinding method and assign the value to ECurrentMethod enum (if active button is NOT a nullptr)
		if (this->m_algorithmsPanel->GetActiveButton())
		{
			this->m_eCurrentMethod = static_cast<E_PATHDINDER_METHOD>(this->m_algorithmsPanel->GetActiveButton()->GetID());
		}
		
		this->HandleInput(tEvent.mouseButton.button, true);

		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		this->HandleInput(tEvent.mouseButton.button, false);
		break;
	}
	}
}

void Application::HandleInput(sf::Mouse::Button pButton, bool pPressed)
{
	/*if (pPressed)
	{*/
		switch (pButton)
		{
		case sf::Mouse::Left:
		{
			if (pPressed)
			{
				this->m_leftMouseBtnPressed = true;
			}
			else
			{
				this->m_leftMouseBtnPressed = false;
			}
		

			break;
		}
		case sf::Mouse::Right:
		{
			break;
		}
		case sf::Mouse::Middle:
		{
			break;
		}
		}
		// Check which method is active and run active method (if any)
		switch (this->m_eCurrentMethod)
		{
		case E_PATHDINDER_METHOD::E_ASTAR:
		{
			this->tPathFinder.SolveAStar(this->m_grid);
			break;
		}
		case E_PATHDINDER_METHOD::E_DIJKSTRA:
			this->tPathFinder.SolveDijkstra(this->m_grid);
			break;
		}
		
	/*}*/

}