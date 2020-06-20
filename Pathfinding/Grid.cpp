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

			tPos.y += tNode.GetShape().getSize().y + pTileSpace;
			Node tNode = Node(false, tPos, pTileSize);
			this->m_vecNodes.push_back(tNode);
			
		}
		tPos.x += tNode.GetShape().getSize().x + pTileSpace;
		tPos.y = this->m_gridPosition.y;
	}


	//Create connections between the nodes
	for(int x = 0; x < pWidth; x++)
		for (int y = 0; y < pHeight; y++)
		{
			if (y > 0)
			{
				this->m_vecNodes[y*pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y - 1) * pWidth + (x + 0)]);
			}
			if (y < pHeight - 1)
			{
				this->m_vecNodes[y*pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y + 1) * pWidth + (x + 0)]);
			}
			if (x > 0)
			{
				m_vecNodes[y * pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y + 0) * pWidth + (x - 1)]);
			}
			if (x < pWidth - 1)
			{
				m_vecNodes[y * pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y + 0) * pWidth + (x + 1)]);
			}



			// Create Diagonal connections between nodes
			if (y > 0 && x > 0)
			{
				m_vecNodes[y*pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y - 1) * pWidth + (x - 1)]);
			}
			if (y < pHeight - 1 && x > 0)
			{
				m_vecNodes[y*pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y + 1) * pWidth + (x - 1)]);
			}
			if (y > 0 && x < pWidth - 1)
			{
				m_vecNodes[y*pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y - 1) * pWidth + (x + 1)]);
			}
			if (y < pWidth - 1 && x < pWidth - 1)
			{
				m_vecNodes[y*pWidth + x].GetNeighbours().push_back(&m_vecNodes[(y + 1) * pWidth + (x + 1)]);
			}
		}
	//Manually position the starting and ending nodes so they are no longer nullptr
	m_startNode = &m_vecNodes[(pHeight / 2) * pWidth + 1];
	m_endNode = &m_vecNodes[(pHeight / 2) * pWidth + pWidth - 2];

	//Set the initial colors for start and end nodes
	m_startNode->GetShape().setFillColor(sf::Color::Green);
	m_endNode->GetShape().setFillColor(sf::Color::Red);
}

void Grid::ResetGrid()
{
	for (auto& tNode : this->m_vecNodes)
	{
		// Reset the node if it is not a start/end node
		if (&tNode != m_endNode && &tNode != m_startNode)
		{
			SetNodeAsNonObstacle(tNode);
			SetNodeAsUnvisited(tNode);
		}
	}
}


void Grid::SetNewStartNode(Node& pNode)
{
	//Set the color of current StartNode to white
	this->m_startNode->GetShape().setFillColor(sf::Color::White);
	//Then set the pointer to null
	this->m_startNode = nullptr;
	// Point to a new start node
	this->m_startNode = &pNode;

	//Set the color of this node as Green
	pNode.GetShape().setFillColor(sf::Color::Green);
}

void Grid::SetNewEndNode(Node& pNode)
{
	//Set the color of current EndNode to white
	this->m_endNode->GetShape().setFillColor(sf::Color::White);
	//Then set the pointer to null
	this->m_endNode = nullptr;
	// Point to a new end node
	this->m_endNode = &pNode;

	//Set the color of this node as Red
	pNode.GetShape().setFillColor(sf::Color::Red);
}

void Grid::SetNodeAsUnvisited(Node& pNode)
{
	//Check if the node is a start/end node
	if (&pNode != this->m_startNode && &pNode != this->m_endNode )
	{
		pNode.SetAsVisited(false);
		pNode.GetShape().setFillColor(sf::Color::White);
	}
	else
	{
		pNode.SetAsVisited(false);
	}
}

void Grid::SetNodeAsVisited(Node& pNode)
{
	//Check if the node is a start/end node
	if (&pNode != this->m_startNode && &pNode != this->m_endNode)
	{
		pNode.SetAsVisited(true); 
		pNode.GetShape().setFillColor(sf::Color::Yellow);
	}
	else
	{
		pNode.SetAsVisited(true);
	}
}

void Grid::SetNodeAsObstacle(Node& pNode)
{
	if (&pNode != this->m_startNode && &pNode != this->m_endNode)
	{
		pNode.SetAsObstacle(true);
		pNode.GetShape().setFillColor(sf::Color::Magenta);
	}
}

void Grid::SetNodeAsNonObstacle(Node& pNode)
{
	if (&pNode != this->m_startNode && &pNode != this->m_endNode)
	{
		pNode.SetAsObstacle(false);
		pNode.GetShape().setFillColor(sf::Color::White);
	}
}

void Grid::DrawNodes(E_ACTIVE_NODE pActiveNodeType, MousePointer& pMousePointer)
{
	switch (pActiveNodeType)
	{
	case E_ACTIVE_NODE::E_NODE_NONE:
		break;

	case E_ACTIVE_NODE::E_NODE_START:
	{
		for (auto& tNode : this->m_vecNodes)
		{
			if (tNode.GetShape().getGlobalBounds().intersects(pMousePointer.getBoundingBox()) && &tNode != m_endNode && !tNode.IsObstacle())
			{
				//Set the clicked node as the new StartNode
				SetNewStartNode(tNode);
			}
		}
		break;
	}
	case E_ACTIVE_NODE::E_NODE_END:
	{
		for (auto& tNode : this->m_vecNodes)
		{
			if (tNode.GetShape().getGlobalBounds().intersects(pMousePointer.getBoundingBox()) && &tNode != m_startNode && !tNode.IsObstacle())
			{
				//Set the clicked node as the new EndNode
				SetNewEndNode(tNode);
			}
		}
		break;
	}
	case E_ACTIVE_NODE::E_NODE_OBSTACLE:
	{

		for (auto& tNode : this->m_vecNodes)
		{
			if (tNode.GetShape().getGlobalBounds().intersects(pMousePointer.getBoundingBox()))
			{
				if (!tNode.IsObstacle())
				{
					SetNodeAsObstacle(tNode);
				}
			}
		}
		break;
	}
	case E_ACTIVE_NODE::E_NODE_NO_OBSTACLE:
		for (auto& tNode : this->m_vecNodes)
		{
		if(tNode.GetShape().getGlobalBounds().intersects(pMousePointer.getBoundingBox()))
		{
			if (tNode.IsObstacle())
			{
				SetNodeAsNonObstacle(tNode);
			}
		}
		}
	}
}