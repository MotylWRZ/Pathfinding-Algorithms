#include "Node.h"



Node::Node(bool pObstacle, sf::Vector2f pPosition)
	: m_bObstacle(pObstacle)
	, m_position(pPosition)
	, m_parentNode(nullptr)
	, m_bVisited(false)
{
	this->m_rectShape.setPosition(m_position);
	this->m_rectShape.setSize(sf::Vector2f(50.0f, 50.0f));
}


Node::~Node()
{
}
