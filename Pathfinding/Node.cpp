#include "Node.h"



Node::Node(bool pWalkable, sf::Vector2f pPosition)
	: m_bWalkable(pWalkable)
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
