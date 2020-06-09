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
	

{
	//Initialise Mouse Pointer
	this->m_mousePointer.Initialise(this->m_window);

	//Create a grid of nodes
	this->m_grid.createGrid(sf::Vector2f(100.0f, 100.0f), 20, 20, sf::Vector2f(20.0f, 20.0f), 1.0f);

	//Create GUI
	this->m_GUI = new GUI(sf::Vector2f(700.0f, 100.0f));
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);
	this->m_GUI->AddButton(sf::Vector2f(100.0f, 50.0f), "Hello", 1);

	
}


Application::~Application()
{
	delete this->m_GUI;
}

void Application::Update(sf::Time pDeltaTime)
{
	this->m_mousePointer.Update();
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

	this->m_GUI->Render(this->m_window);

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
	if (pPressed)
	{
		switch (pButton)
		{
		case sf::Mouse::Left:
		{

			for (auto& tNode : m_grid.m_vecNodes)
			{
				if (tNode.m_rectShape.getGlobalBounds().intersects(this->m_mousePointer.getBoundingBox()))
				{
					//Set the clicked node as the new StartNode
					m_grid.SetNewStartNode(tNode);
				}

			}

			break;
		}
		case sf::Mouse::Right:
		{
			for (auto& tNode : m_grid.m_vecNodes)
			{
				if (tNode.m_rectShape.getGlobalBounds().intersects(this->m_mousePointer.getBoundingBox()))
				{
					//Set the clicked node as the new EndNode
					m_grid.SetNewEndNode(tNode);
					
				}

			}
			break;
		}

		case sf::Mouse::Middle:
		{
			for (auto& tNode : m_grid.m_vecNodes)
			{
				if (tNode.m_rectShape.getGlobalBounds().intersects(this->m_mousePointer.getBoundingBox()))
				{
					if (!tNode.m_bObstacle)
					{
						m_grid.SetNodeAsObstacle(tNode);
					}
					else
					{
						m_grid.SetNodeAsNonObstacle(tNode);
					}
					

				}

			}
			break;
		}
		}
		this->tPathFinder.SolveAStar(this->m_grid);
		
	}

}