#pragma once
#include <iostream>
#include <vector>
# include "Graph.h"
# include "Node.h"
#include <queue>
#include <unordered_map>
#include <time.h> 
#include "Vector2D.h" 
#include <functional>
#include "MyPriorityQueue.h"

class Dijkstra
{
public:
	Dijkstra();
	float RandomFloat(float a, float b);
	std::vector<Vector2D> DijkstraSearch(Graph graph, Node root, Node goal);
	std::vector<Node> visited;
	~Dijkstra();
private:

};

