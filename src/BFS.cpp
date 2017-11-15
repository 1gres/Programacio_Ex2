#include "BFS.h"

BFS::BFS() {

}

std::vector<Node> BFS::BFSSearch(Graph graph, Node root, Node goal)
{

	std::queue<Node> frontier;
	Node current(0,0);
	Node from(0,0), to(0,0);

	Connection next(from,to,1);
	std::vector<Connection> connections;
	root.visited = true;

	frontier.push(root);
	//std::cout << "Node root x: " << root.pos.x << "\nNode root y: " << root.pos.y << std::endl;

	std::vector<std::pair<Node,Node>> came_from;

	while (!frontier.empty())
	{
		current = frontier.front();
		frontier.pop();
		if (current.pos == goal.pos) {
			break;
		}
		connections = graph.GetConnections(current);
		for (unsigned int i = 0; i < connections.size(); i++) {
			next = connections[i];
			if (!next.GetToNode().visited) {
				frontier.push(next.to);
				next.to.visited = true;
				came_from.push_back(std::make_pair(next.GetToNode(),current));
			}
			
		}
		std::cout << "x: " << current.pos.x << std::endl;
		std::cout << "y: " << current.pos.y << std::endl;

	}
	
	std::vector<Node> came_from_converted;
	for (unsigned int i = 0; i < came_from.size(); i++) {
		came_from_converted.push_back(came_from[i].second);
	}
	return came_from_converted;
}


BFS::~BFS()
{
}
