#pragma once
#include <iostream>
#include <vector>
# include "Graph.h"
# include "Node.h"
#include <queue>
#include <unordered_map>
#include <time.h> 


class Dijkstra
{
public:
	Dijkstra();
	std::vector<Vector2D> DijkstraSearch(Graph graph, Node root, Node goal);
	~Dijkstra();
private:

};
