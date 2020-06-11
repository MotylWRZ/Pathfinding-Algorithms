#include "Pathfinder.h"

#include <list>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>

Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}

float Pathfinder::CalculateNodesDistance(Node* pNodeA, Node* pNodeB)
{
	return sqrtf((pNodeA->m_position.x - pNodeB->m_position.x)*(pNodeA->m_position.x - pNodeB->m_position.x) +
		(pNodeA->m_position.y - pNodeB->m_position.y)*(pNodeA->m_position.y - pNodeB->m_position.y));
}


void Pathfinder::SolveAStar(Grid& pGrid)
{
	//Reset Navigation graph - default states for all nodes
	for(int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{
			
			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_bObstacle)
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_gCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_hCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_parentNode = nullptr;
		}

	//Setup Starting conditions
	//Create a pointer to current node that is explored
	Node* tCurrentNode = pGrid.m_startNode;
	pGrid.m_startNode->m_gCost = 0.0f;
	pGrid.m_startNode->m_hCost = CalculateNodesDistance(pGrid.m_startNode, pGrid.m_endNode); //Calculate heuristic
	
	//Add a list for notVisited nodes and add to it a startNode
	std::list<Node*> tListNotVisitedNodes;
	tListNotVisitedNodes.push_back(pGrid.m_startNode);

	while (!tListNotVisitedNodes.empty() && tCurrentNode != pGrid.m_endNode)
	{
		
		//Sort Unvisited nodes by global goal, so node with lowest cost first
		tListNotVisitedNodes.sort([](const Node* lhs, const Node* rhs) {return lhs->m_hCost < rhs->m_hCost; });

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
			float tLowerGoal = tCurrentNode->m_gCost + CalculateNodesDistance(tCurrentNode, tNodeNeighbour);

			if (tLowerGoal < tNodeNeighbour->m_gCost)
			{
				tNodeNeighbour->m_parentNode = tCurrentNode;
				tNodeNeighbour->m_gCost = tLowerGoal;

				tNodeNeighbour->m_hCost = tNodeNeighbour->m_gCost + CalculateNodesDistance(tNodeNeighbour, pGrid.m_endNode); //Calculate heuristic between neighbour and endNode
			}
		}
		
	}
	// Draw the final path
	DrawPath(pGrid);
}

void Pathfinder::SolveDijkstra(Grid& pGrid)
{
	
	//Reset Navigation graph - default states for all nodes
	for (int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{

			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_bObstacle)
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_gCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_hCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_parentNode = nullptr;
		}
	//Setup Starting conditions
	//Create a pointer to current node that is explored
	Node* tCurrentNode = pGrid.m_startNode;
	pGrid.m_startNode->m_gCost = 0.0f;
	pGrid.m_startNode->m_hCost = 0.0f; //hCost = 0 as heuristic in Dijkstra == 0

	typedef std::pair<float, Node*> tNodeDistPair; // Create a pair with float(gCost) and Node pointer)
	tNodeDistPair tCurrentNodePair;
	tCurrentNodePair = std::make_pair(tCurrentNode->m_gCost, tCurrentNode); // make a pair of the Gcost and the Current node

	//Add a priority queue for notVisited nodes and add to it a startNodePair
	std::priority_queue<tNodeDistPair, std::vector<tNodeDistPair>, std::greater<tNodeDistPair>> tListNotVisitedNodes;
	tListNotVisitedNodes.push(tCurrentNodePair);

	// keep looping until the queue will be empty or the Current node will be the end node
	while (!tListNotVisitedNodes.empty() && tCurrentNode != pGrid.m_endNode)
	{
		// Go to the node with the lowest cost (top() will return the element with the lowest first valuie (float gCost))
		tCurrentNode = tListNotVisitedNodes.top().second;
		// Set a current NodePair from the CurrentNode and its gCost
		tCurrentNodePair = std::make_pair(tCurrentNode->m_gCost, tCurrentNode);
		//Dequeue the top element (the one with the lowest gCost)
		tListNotVisitedNodes.pop();
		//Set the current node as visited
		pGrid.SetNodeAsVisited(*tCurrentNode);

		// Loop over all current node's neighbours
		for (int i = 0; i < tCurrentNode->m_vecNeighbours.size(); ++i)
		{
			Node* tNeighbour = tCurrentNode->m_vecNeighbours[i];
			//skip the neighbour if it has been visited already, is an obstacle or if Current node is an endNode
			if (tNeighbour->m_bVisited || tNeighbour->m_bObstacle || tCurrentNode == pGrid.m_endNode)
			{
				continue;
			}
			// Calculate the lower goal from Gcost and the current distance between this neigbour and the current node
			float tLowerGoal = tCurrentNode->m_gCost + CalculateNodesDistance(tCurrentNode, tNeighbour);

			// If the Lower goal value is < the gCost of the current neighbour
			if (tLowerGoal < tNeighbour->m_gCost)
			{
				// Update the gCost of this neighbour 
				tNeighbour->m_gCost = tLowerGoal;
				// Set the parent node as the current node for this neighbour
				tNeighbour->m_parentNode = tCurrentNode;
				// Set the currentNodePair as the current neigbour's gCost and the pointer to it
				tCurrentNodePair = std::make_pair(tNeighbour->m_gCost, tNeighbour);
				// Enqueue the currentNodePair
				tListNotVisitedNodes.push(tCurrentNodePair);
				// Set this neighbour as visisted node
				pGrid.SetNodeAsVisited(*tNeighbour);
			}
		}
	}
	// Draw the final path
	DrawPath(pGrid);
}

void Pathfinder::SolveBFS(Grid& pGrid)
{

	//Reset Navigation graph - default states for all nodes
	for (int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{

			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_bObstacle)
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_gCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_hCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_parentNode = nullptr;
		}

	//set the current node as startNode
	Node* tCurrentNode = pGrid.m_startNode;

	std::queue<Node*> tOpenlist;

	//Set current visited node as visited and enqueue it
	
	tOpenlist.push(tCurrentNode);
	
	pGrid.SetNodeAsVisited(*tCurrentNode);

	//while the open list is not empty
	while (!tOpenlist.empty())
	{
		//take the front node from queue
		tCurrentNode = tOpenlist.front();
		tOpenlist.pop(); // Dequeue the first element
		pGrid.SetNodeAsVisited(*tCurrentNode); // set current node as visited

		// if the end has been reached
		if (tCurrentNode == pGrid.m_endNode)
		{
			break;
		}

		for (int i = 0; i < tCurrentNode->m_vecNeighbours.size(); ++i)
		{
			Node* tNeighbour= tCurrentNode->m_vecNeighbours[i];
			//skip the neighbour if it has been visited already or it is an obstacle
			if (tNeighbour->m_bVisited || tNeighbour->m_bObstacle)
			{
				continue;
			}

			tOpenlist.push(tNeighbour);
			pGrid.SetNodeAsVisited(*tNeighbour);
			tNeighbour->m_parentNode = tCurrentNode;
		}
		DrawPath(pGrid);
	}
	
}



void Pathfinder::Reset(Grid& pGrid)
{
	//Reset Navigation graph - default states for all nodes
	for (int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{

			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_bObstacle)
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_gCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_hCost = INFINITY;
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].m_parentNode = nullptr;
		}
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