#include "Pathfinder.h"

#include <list>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>

Pathfinder::Pathfinder()
	: m_bPathDrawn(false)
{
}


Pathfinder::~Pathfinder()
{
}

float Pathfinder::CalculateNodesDistance(Node* pNodeA, Node* pNodeB)
{
	return sqrtf((pNodeA->GetPosition().x - pNodeB->GetPosition().x)*(pNodeA->GetPosition().x - pNodeB->GetPosition().x) +
		(pNodeA->GetPosition().y - pNodeB->GetPosition().y)*(pNodeA->GetPosition().y - pNodeB->GetPosition().y));
}


void Pathfinder::SolveAStar(Grid& pGrid)
{
	//Reset Navigation graph - default states for all nodes
	for(int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{
			
			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].IsObstacle())
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetGCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetHCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetParentNode(nullptr);
		}

	//Setup Starting conditions
	//Create a pointer to current node that is explored
	Node* tCurrentNode = pGrid.m_startNode;
	pGrid.m_startNode->SetGCost(0.0f);
	pGrid.m_startNode->SetHCost(CalculateNodesDistance(pGrid.m_startNode, pGrid.m_endNode)); //Calculate heuristic
	

	typedef std::pair<float, Node*> tNodeDistPair; // Create a pair with float(gCost) and Node pointer)
	tNodeDistPair tCurrentNodePair;
	tCurrentNodePair = std::make_pair(tCurrentNode->GetHCost(), tCurrentNode); // make a pair of the Gcost and the Current node

	//Add a priority queue for notVisited nodes and add to it a startNodePair
	std::priority_queue<tNodeDistPair, std::vector<tNodeDistPair>, std::greater<tNodeDistPair>> tListNotVisitedNodes;
	tListNotVisitedNodes.push(tCurrentNodePair);


	while (!tListNotVisitedNodes.empty() && tCurrentNode != pGrid.m_endNode)
	{
		
		// Go to the node with the lowest cost (top() will return the element with the lowest first valuie (float gCost))
		tCurrentNode = tListNotVisitedNodes.top().second;
		// Set a current NodePair from the CurrentNode and its gCost
		tCurrentNodePair = std::make_pair(tCurrentNode->GetHCost(), tCurrentNode);
		//Dequeue the top element (the one with the lowest gCost)
		tListNotVisitedNodes.pop();
		//Set the current node as visited
		pGrid.SetNodeAsVisited(*tCurrentNode);

		// Loop over all current node's neighbours
		for (auto tNodeNeighbour : tCurrentNode->GetNeighbours())
		{
			Node* tNeighbour = tNodeNeighbour;
			//skip the neighbour if it has been visited already, is an obstacle or if Current node is an endNode
			if (tNeighbour->IsVisited()|| tNeighbour->IsObstacle() || tCurrentNode == pGrid.m_endNode)
			{
				continue;
			}
			// Calculate the lower goal from Gcost and the current distance between this neigbour and the current node
			float tLowerGoal = tCurrentNode->GetGCost() + CalculateNodesDistance(tCurrentNode, tNeighbour);

			// If the Lower goal value is < the gCost of the current neighbour
			if (tLowerGoal < tNeighbour->GetGCost())
			{
				// Update the gCost of this neighbour 
				tNeighbour->SetGCost(tLowerGoal);
				//Calculate heuristic between neighbour and endNode
				tNodeNeighbour->SetHCost(tNodeNeighbour->GetGCost() + CalculateNodesDistance(tNodeNeighbour, pGrid.m_endNode));
				// Set the parent node as the current node for this neighbour
				tNeighbour->SetParentNode(tCurrentNode);
				// Set the currentNodePair as the current neigbour's gCost and the pointer to it
				tCurrentNodePair = std::make_pair(tNeighbour->GetHCost(), tNeighbour);
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

void Pathfinder::SolveDijkstra(Grid& pGrid)
{
	
	//Reset Navigation graph - default states for all nodes
	for (int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{

			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].IsObstacle())
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetGCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetHCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetParentNode(nullptr);
		}
	//Setup Starting conditions
	//Create a pointer to current node that is explored
	Node* tCurrentNode = pGrid.m_startNode;
	pGrid.m_startNode->SetGCost(0.0f);
	pGrid.m_startNode->SetHCost(0.0f); //hCost = 0 as heuristic in Dijkstra == 0

	typedef std::pair<float, Node*> tNodeDistPair; // Create a pair with float(gCost) and Node pointer)
	tNodeDistPair tCurrentNodePair;
	tCurrentNodePair = std::make_pair(tCurrentNode->GetGCost(), tCurrentNode); // make a pair of the Gcost and the Current node

	//Add a priority queue for notVisited nodes and add to it a startNodePair
	std::priority_queue<tNodeDistPair, std::vector<tNodeDistPair>, std::greater<tNodeDistPair>> tListNotVisitedNodes;
	tListNotVisitedNodes.push(tCurrentNodePair);

	// keep looping until the queue will be empty or the Current node will be the end node
	while (!tListNotVisitedNodes.empty() && tCurrentNode != pGrid.m_endNode)
	{
		// Go to the node with the lowest cost (top() will return the element with the lowest first valuie (float gCost))
		tCurrentNode = tListNotVisitedNodes.top().second;
		// Set a current NodePair from the CurrentNode and its gCost
		tCurrentNodePair = std::make_pair(tCurrentNode->GetGCost(), tCurrentNode);
		//Dequeue the top element (the one with the lowest gCost)
		tListNotVisitedNodes.pop();
		//Set the current node as visited
		pGrid.SetNodeAsVisited(*tCurrentNode);

		// Loop over all current node's neighbours
		for (int i = 0; i < tCurrentNode->GetNeighbours().size(); ++i)
		{
			Node* tNeighbour = tCurrentNode->GetNeighbours()[i];
			//skip the neighbour if it has been visited already, is an obstacle or if Current node is an endNode
			if (tNeighbour->IsVisited() || tNeighbour->IsObstacle() || tCurrentNode == pGrid.m_endNode)
			{
				continue;
			}
			// Calculate the lower goal from Gcost and the current distance between this neigbour and the current node
			float tLowerGoal = tCurrentNode->GetGCost() + CalculateNodesDistance(tCurrentNode, tNeighbour);

			// If the Lower goal value is < the gCost of the current neighbour
			if (tLowerGoal < tNeighbour->GetGCost())
			{
				// Update the gCost of this neighbour 
				tNeighbour->SetGCost(tLowerGoal);
				// Set the parent node as the current node for this neighbour
				tNeighbour->SetParentNode(tCurrentNode);
				// Set the currentNodePair as the current neigbour's gCost and the pointer to it
				tCurrentNodePair = std::make_pair(tNeighbour->GetGCost(), tNeighbour);
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
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].IsObstacle())
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetGCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetHCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetParentNode(nullptr);
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

		for (int i = 0; i < tCurrentNode->GetNeighbours().size(); ++i)
		{
			Node* tNeighbour= tCurrentNode->GetNeighbours()[i];
			//skip the neighbour if it has been visited already or it is an obstacle
			if (tNeighbour->IsVisited()|| tNeighbour->IsObstacle())
			{
				continue;
			}

			tOpenlist.push(tNeighbour);
			pGrid.SetNodeAsVisited(*tNeighbour);
			tNeighbour->SetParentNode(tCurrentNode);
		}
		DrawPath(pGrid);
	}
	
}



void Pathfinder::Reset(Grid& pGrid)
{
	// Do not continue if path is not drawn
	if (!this->m_bPathDrawn)
		return;

	//Reset Navigation graph - default states for all nodes
	for (int x = 0; x < pGrid.m_GridWidth; x++)
		for (int y = 0; y < pGrid.m_GridHeight; y++)
		{

			//If node is NOT an obstacle, set it an Unvisisted
			if (!pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].IsObstacle())
			{
				pGrid.SetNodeAsUnvisited(pGrid.m_vecNodes[y*pGrid.m_GridWidth + x]);
			}
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetGCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetHCost(INFINITY);
			pGrid.m_vecNodes[y*pGrid.m_GridWidth + x].SetParentNode(nullptr);
		}

	this->m_bPathDrawn = false;
}

void Pathfinder::DrawPath(Grid& pGrid)
{
	if (pGrid.m_endNode != nullptr)
	{
		Node* tPath = pGrid.m_endNode;
		
		while (tPath->getParentNode() != nullptr && tPath->getParentNode() != pGrid.m_startNode)
		{
			tPath->getParentNode()->GetShape().setFillColor(sf::Color::Blue);
			tPath = tPath->getParentNode();
		}

		this->m_bPathDrawn = true;
	}
}