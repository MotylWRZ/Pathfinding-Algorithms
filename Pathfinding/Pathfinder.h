#pragma once
#include "Grid.h"
class Pathfinder
{
public:
	Pathfinder();
	virtual ~Pathfinder();

	void SolveAStar(Grid& pGrid);
	void DrawPath(Grid& pGrid);

};

