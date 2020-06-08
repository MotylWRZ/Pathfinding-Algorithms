#include "Grid.h"



Grid::Grid()
	: m_startNode(nullptr)
	, m_endNode(nullptr)
{
}


Grid::~Grid()
{
}


void Grid::createGrid(sf::Vector2f pGridPosition, int pWidth, int pHeight, sf::Vector2f pTileSize, float pTileSpace)
{
	this->m_GridWidth = pWidth;
	this->m_GridHeight = pHeight;

	//Set grid world position
	m_gridPosition = pGridPosition;



	sf::Vector2f tPos = this->m_gridPosition;
	//Create a grid of nodes
	for (int i = 0; i < pWidth; i++)
	{
		Node tNode = Node(false, tPos, pTileSize);
		this->m_vecNodes.push_back(tNode);
		for (int j = 1; j < pHeight; j++)
		{

			tPos.y += tNode.m_rectShape.getSize().y + pTileSpace;
			Node tNode = Node(false, tPos, pTileSize);
			this->m_vecNodes.push_back(tNode);
			
		}
		tPos.x += tNode.m_rectShape.getSize().x + pTileSpace;
		tPos.y = this->m_gridPosition.y;
	}


	//Create connections between the nodes
	for(int x = 0; x < pWidth; x++)
		for (int y = 0; y < pHeight; y++)
		{
			if (y > 0)
			{
				this->m_vecNodes[y*pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y - 1) * pWidth + (x + 0)]);
			}
			if (y < pHeight - 1)
			{
				this->m_vecNodes[y*pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y + 1) * pWidth + (x + 0)]);
			}
			if (x > 0)
			{
				m_vecNodes[y * pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y + 0) * pWidth + (x - 1)]);
			}
			if (x < pWidth - 1)
			{
				m_vecNodes[y * pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y + 0) * pWidth + (x + 1)]);
			}



			// Create Diagonal connections between nodes
			if (y > 0 && x > 0)
			{
				m_vecNodes[y*pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y - 1) * pWidth + (x - 1)]);
			}
			if (y < pHeight - 1 && x > 0)
			{
				m_vecNodes[y*pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y + 1) * pWidth + (x - 1)]);
			}
			if (y > 0 && x < pWidth - 1)
			{
				m_vecNodes[y*pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y - 1) * pWidth + (x + 1)]);
			}
			if (y < pWidth - 1 && x < pWidth - 1)
			{
				m_vecNodes[y*pWidth + x].m_vecNeighbours.push_back(&m_vecNodes[(y + 1) * pWidth + (x + 1)]);
			}
		}

	
	

	//Manually position the starting and ending nodes so they are no longer nullptr
	m_startNode = &m_vecNodes[(pHeight / 2) * pWidth + 1];
	m_endNode = &m_vecNodes[(pHeight / 2) * pWidth + pWidth - 2];

	m_startNode->m_rectShape.setFillColor(sf::Color::Green);
	m_endNode->m_rectShape.setFillColor(sf::Color::Red);
}


void Grid::SetNewStartNode(Node& pNode)
{
	//Set the color of current StartNode to white
	this->m_startNode->m_rectShape.setFillColor(sf::Color::White);
	//Then set the pointer to null
	this->m_startNode = nullptr;
	// Point to a new start node
	this->m_startNode = &pNode;
	pNode.m_rectShape.setFillColor(sf::Color::Green);
}

void Grid::SetNewEndNode(Node& pNode)
{
	//Set the color of current EndNode to white
	this->m_endNode->m_rectShape.setFillColor(sf::Color::White);
	//Then set the pointer to null
	this->m_endNode = nullptr;
	// Point to a new end node
	this->m_endNode = &pNode;
	pNode.m_rectShape.setFillColor(sf::Color::Red);
}

void Grid::SetNodeAsUnvisited(Node& pNode)
{
	//Check if the node is a start/end node
	if (&pNode != this->m_startNode && &pNode != this->m_endNode )
	{
		pNode.m_bVisited = false;
		pNode.m_rectShape.setFillColor(sf::Color::White);
	}
}

void Grid::SetNodeAsVisited(Node& pNode)
{
	//Check if the node is a start/end node
	if (&pNode != this->m_startNode && &pNode != this->m_endNode)
	{
		pNode.m_bVisited = true;
		pNode.m_rectShape.setFillColor(sf::Color::Yellow);
	}
}

void Grid::SetNodeAsObstacle(Node& pNode)
{
	if (&pNode != this->m_startNode && &pNode != this->m_endNode)
	{
		pNode.m_bObstacle = true;
		pNode.m_rectShape.setFillColor(sf::Color::Magenta);
	}
}

void Grid::SetNodeAsNonObstacle(Node& pNode)
{
	if (&pNode != this->m_startNode && &pNode != this->m_endNode)
	{
		pNode.m_bObstacle = false;
		pNode.m_rectShape.setFillColor(sf::Color::White);
	}
}