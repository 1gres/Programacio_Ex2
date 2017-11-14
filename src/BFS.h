#pragma once
#include <iostream>
#include <vector>
# include "Graph.h"
# include "Node.h"
#include <queue>

class BFS
{
public:
	BFS();
	std::vector<Node> BFSSearch(Graph graph, Node root, Node goal);
	~BFS();
private:
	
};

