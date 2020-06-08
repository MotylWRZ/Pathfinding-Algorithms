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
	void SetNodeAsUnvisited(Node& pNode);
	void SetNodeAsVisited(Node& pNode);
	void SetNodeAsObstacle(Node& pNode);
	void SetNodeAsNonObstacle(Node& pNode);


	//Class members
	int m_GridWidth;
	int m_GridHeight;
	
	sf::Vector2f m_gridPosition;

	//vector of nodes
	std::vector<Node> m_vecNodes;

	Node* m_startNode;
	Node* m_endNode;
};

