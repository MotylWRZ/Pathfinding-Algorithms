#pragma once
#include <SFML/Graphics.hpp>
class Node
{
public:
	Node(bool pObstacle, sf::Vector2f pPosition, sf::Vector2f pTileSize);
	virtual ~Node();


	//Accesors/Mutators
	inline Node* getParentNode() { return m_parentNode; };
	inline float GetGCost() { return m_gCost; };
	inline float GetHCost() { return m_hCost; };
	inline float GetFCost() { return m_fCost = m_gCost + m_hCost; };
	inline std::vector<Node*>& GetNeighbours() { return m_vecNeighbours; };
	inline sf::Vector2f GetPosition() { return m_position; };
	inline sf::RectangleShape& GetShape() { return m_rectShape; };
	inline bool IsObstacle() { return m_bObstacle; };
	inline bool IsVisited() { return m_bVisited; };

	inline void SetParentNode(Node* pParent) { m_parentNode = pParent; };
	inline void SetGCost(float pGCost) { m_gCost = pGCost; };
	inline void SetHCost(float pHCost) { m_hCost = pHCost; };
	inline void SetAsObstacle(bool pIsObstacle) { m_bObstacle = pIsObstacle; };
	inline void SetAsVisited(bool pIsVisited) { m_bVisited = pIsVisited; };


private:
	bool m_bObstacle;
	bool m_bVisited;
	
	float m_gCost; // Distance from starting point	
	float m_hCost; // Distance from endNode
	float m_fCost; // gCost and hCost combined

	Node* m_parentNode; // Pointer to parent node (previous node)

	std::vector<Node*> m_vecNeighbours; // vector storing pointers to all neighbours

	sf::Vector2f m_position;
	sf::RectangleShape m_rectShape;
};

