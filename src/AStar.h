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

class AStar
{
public:
	AStar();
	int random();
	std::vector<float> costos;
	float Heuristic(Vector2D a, Vector2D b);
	std::vector<Vector2D> AStarSearch(Graph graph, Node root, Node goal);
	std::vector<Node> visited;
	~AStar();
};

