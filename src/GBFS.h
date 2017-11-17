#pragma once
#include <iostream>
#include <vector>
# include "Graph.h"
# include "Node.h"
#include <queue>
#include <unordered_map>
#include "Vector2D.h" 
#include <functional>
#include "MyPriorityQueue.h"


class GBFS
{
public:
	GBFS();
	float RandomFloat(float a, float b);
	float Heuristic(Vector2D a, Vector2D b);
	std::vector<Vector2D> GBFSSearch(Graph graph, Node root, Node goal);
	~GBFS();
private:

};

