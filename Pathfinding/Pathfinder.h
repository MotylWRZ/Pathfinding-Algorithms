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
	void DrawPath(Grid& pGrid);

	float CalculateNodesDistance(Node* pNodeA, Node* pNodeB);
	float CalculateNodesHeuristic(Node* pNodeA, Node* pNodeB);
};

