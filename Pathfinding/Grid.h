#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "Node.h"


class Grid
{
public:
	Grid();
	virtual ~Grid();

	void createGrid(sf::Vector2f pGridPosition,int  pWidth, int pHeight);
	
	


	//Accesors/Mutators
	void SetNewStartNode(Node& pNode);
	void SetNewEndNode(Node& pNode);


	//Class members

	
	sf::Vector2f m_gridPosition;

	//vector of nodes
	std::vector<Node> m_vecNodes;

	Node* m_startNode;
	Node* m_endNode;
};

