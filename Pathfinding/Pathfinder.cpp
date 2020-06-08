#include "Pathfinder.h"

#include <list>
#include <algorithm>
#include <string>

Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}


void Pathfinder::SolveAStar(Grid& pGrid)
{
	//Reset Navigation graph - default states for all nodes
	for(int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{
			
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_bVisited = false;
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_bObstacle)
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]); // Experimental
			}
			
			//check it later
			/*pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_gCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_hCost = INFINITY;*/
			
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_localGoal = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_globalGoal = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_parentNode = nullptr;
		}

	//use lambda function to calculate the distance between nodes
	auto distance = [](Node* a, Node* b)
	{
		return sqrtf((a->m_position.x - b->m_position.x)*(a->m_position.x - b->m_position.x) + (a->m_position.y - b->m_position.y)*(a->m_position.y - b->m_position.y));
	};

	//another lmbda function to calculate the heuristic
	auto heuristic = [distance](Node* a, Node* b)
	{
		return distance(a, b);
	};

	//Setup Starting conditions
	//Create a pointer to current node that is explored
	Node* tCurrentNode = pGrid.m_startNode;
	pGrid.m_startNode->m_localGoal = 0.0f;
	pGrid.m_startNode->m_globalGoal = heuristic(pGrid.m_startNode, pGrid.m_endNode);
	
	//Add a list for notVisited nodes and add to it a startNode
	std::list<Node*> tListNotVisitedNodes;
	tListNotVisitedNodes.push_back(pGrid.m_startNode);

	while (!tListNotVisitedNodes.empty() && tCurrentNode != pGrid.m_endNode)
	{
		
		//Sort Unvisited nodes by global goal, so node with lowest cost first
		tListNotVisitedNodes.sort([](const Node* lhs, const Node* rhs) {return lhs->m_globalGoal < rhs->m_globalGoal; });

		while (!tListNotVisitedNodes.empty() && tListNotVisitedNodes.front()->m_bVisited)
			tListNotVisitedNodes.pop_front();

		if (tListNotVisitedNodes.empty())
			break;

		tCurrentNode = tListNotVisitedNodes.front();
		// After the current node have been explored we change the bVisited flag to true
		tCurrentNode->m_bVisited = true; 
		pGrid.SetNodeAsVisited(*tCurrentNode);

		//Check all negighbours of this node
		for (auto tNodeNeighbour : tCurrentNode->m_vecNeighbours)
		{
			//If the neighbour of the current node is NOT visited and is NOT an obstacle, we add
			//it to NotVisited List
			if (!tNodeNeighbour->m_bVisited && tNodeNeighbour->m_bObstacle == 0)
				tListNotVisitedNodes.push_back(tNodeNeighbour);

			// Calculate the neighbours lowest parent distance
			float tLowerGoal = tCurrentNode->m_localGoal + distance(tCurrentNode, tNodeNeighbour);

			if (tLowerGoal < tNodeNeighbour->m_localGoal)
			{
				tNodeNeighbour->m_parentNode = tCurrentNode;
				tNodeNeighbour->m_localGoal = tLowerGoal;

				tNodeNeighbour->m_globalGoal = tNodeNeighbour->m_localGoal + heuristic(tNodeNeighbour, pGrid.m_endNode);
			}
		}
		
	}
	
	DrawPath(pGrid);
}


void Pathfinder::DrawPath(Grid& pGrid)
{
	if (pGrid.m_endNode != nullptr)
	{
		Node* tPath = pGrid.m_endNode;
		
		while (tPath->m_parentNode != nullptr && tPath->m_parentNode != pGrid.m_startNode)
		{
			tPath->m_parentNode->m_rectShape.setFillColor(sf::Color::Blue);
			tPath = tPath->m_parentNode;
		}
	}
}