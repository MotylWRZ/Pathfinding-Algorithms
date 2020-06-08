#include "Node.h"



Node::Node(bool pObstacle, sf::Vector2f pPosition, sf::Vector2f pTileSize)
	: m_bObstacle(pObstacle)
	, m_position(pPosition)
	, m_parentNode(nullptr)
	, m_bVisited(false)
{
	this->m_rectShape.setPosition(m_position);
	this->m_rectShape.setSize(pTileSize);
}


Node::~Node()
{
}
