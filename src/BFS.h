#pragma once
#include <iostream>
#include <vector>
# include "Graph.h"
# include "Node.h"
#include <queue>
#include <unordered_map>


class BFS
{
public:
	BFS();
	std::vector<Vector2D> BFSSearch(Graph graph, Node root, Node goal);
	std::vector<Node> visited;
	~BFS();
private:
	
};

