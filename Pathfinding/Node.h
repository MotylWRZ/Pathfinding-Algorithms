#pragma once
#include <SFML/Graphics.hpp>
class Node
{
public:
	Node(bool pObstacle, sf::Vector2f pPosition, sf::Vector2f pTileSize);
	virtual ~Node();


	//Accesors/Mutators
	inline int GetFCost() { return m_gCost + m_hCost; };
	


public:
	bool m_bObstacle;
	bool m_bVisited;
	
	float m_gCost; // Distance from starting point	
	float m_hCost; // Distance from endNode

	Node* m_parentNode; // Pointer to parent node (previous node)

	std::vector<Node*> m_vecNeighbours; // vector storing pointers to all neighbours

	sf::Vector2f m_position;
	sf::RectangleShape m_rectShape;
};

