#pragma once
#include <SFML/Graphics.hpp>
class Node
{
public:
	Node(bool pWalkable, sf::Vector2f pPosition);
	virtual ~Node();

	inline int GetFCost() { return m_gCost + m_hCost; };

public:
	bool m_bWalkable;
	bool m_bVisited;
	
	int m_gCost;
	int m_hCost;

	Node* m_parentNode;

	std::vector<Node*> m_vecNeighbours;

	sf::Vector2f m_position;
	sf::RectangleShape m_rectShape;
};

