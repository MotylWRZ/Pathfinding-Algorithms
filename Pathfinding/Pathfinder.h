#pragma once
#include "Grid.h"
class Pathfinder
{
public:
	Pathfinder();
	virtual ~Pathfinder();

	void SolveAStar(Grid& pGrid);
	void SolveDijkstra(Grid& pGrid);
	void SolveBFS(Grid& pGrid);
	void Reset(Grid& pGrid);
	void DrawPath(Grid& pGrid);

	float CalculateNodesDistance(Node* pNodeA, Node* pNodeB);

	inline float GetTimeElapsed() { return m_timeElapsed.asSeconds(); };
	inline float GetTotalCost() { return m_totalCost; };

private:
	inline void SetTotalCost(float pCost) { m_totalCost = pCost; };


private:
	bool m_bPathDrawn;
	sf::Clock m_clock;
	sf::Time m_timeElapsed;
	float m_totalCost;

};

