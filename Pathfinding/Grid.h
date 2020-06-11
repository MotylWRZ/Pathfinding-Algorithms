#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "Node.h"
#include "AppStructures.h"
#include "MousePointer.h"



class Grid
{
public:
	Grid();
	virtual ~Grid();

	void createGrid(sf::Vector2f pGridPosition,int  pWidth, int pHeight, sf::Vector2f pTileSize, float pTileSpace);
	void DrawNodes(E_ACTIVE_NODE pActiveNodeType, MousePointer& pMousePointer);
	//Accesors/Mutators
	inline int GetGridWidth() { return m_GridWidth; };
	inline int GetGridHeight() { return m_GridHeight; };
	inline sf::Vector2f GetPosition() { return m_gridPosition; };
	inline std::vector<Node>& GetNodes() { return m_vecNodes; };
	inline Node* GetStartNode() { return m_startNode; };
	inline Node* GetEndNode() { return m_endNode; };

	void SetNewStartNode(Node& pNode);
	void SetNewEndNode(Node& pNode);
	void SetNodeAsUnvisited(Node& pNode);
	void SetNodeAsVisited(Node& pNode);
	void SetNodeAsObstacle(Node& pNode);
	void SetNodeAsNonObstacle(Node& pNode);
	void SetStartNode(Node* pStartNode) { m_startNode = pStartNode; };
	void SetEndNode(Node* pEndNode) { m_endNode = pEndNode; };

private:
	//Class members
	int m_GridWidth;
	int m_GridHeight;
	
	sf::Vector2f m_gridPosition;

	//vector of nodes
	std::vector<Node> m_vecNodes;

	Node* m_startNode;
	Node* m_endNode;
};

