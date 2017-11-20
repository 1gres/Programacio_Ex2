#include "GBFS.h"


GBFS::GBFS() {

}

float GBFS::Heuristic(Vector2D a, Vector2D b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector<Vector2D> GBFS::GBFSSearch(Graph graph, Node root, Node goal)
{
	MyPriorityQueue<Vector2D, float> frontier;

	Node current(0, 0);
	Node from(0, 0), to(0, 0);
	Connection next(from, to, 1);

	std::vector<Connection> connections;

	frontier.put(root.pos, 0.f);

	std::unordered_map<Vector2D, Vector2D> came_from;
	came_from[root.pos] = NULL;

	std::vector<Vector2D> path;

	float priority;
	visited.clear();

	while (!frontier.empty())
	{
		current = frontier.get();

		if (current.pos == goal.pos) {

			path.push_back(current.pos);

			while (current.pos != root.pos)
			{
				current.pos = came_from[current.pos];
				path.push_back(current.pos);
			}

			path.push_back(root.pos);

			std::reverse(path.begin(), path.end());

			return path;
		}
		connections = graph.GetConnections(current);
		for (unsigned int i = 0; i < connections.size(); i++) {
			next = connections[i];

			for (unsigned int j = 0; j < came_from.size(); j++) {
				
				if (came_from.find(next.GetToNode().pos) != came_from.end()) {
					next.to.visited = true;
				}
			}

			if (!next.to.visited) {
				priority = Heuristic(goal.pos, next.GetToNode().pos);
				frontier.put(next.GetToNode().pos, priority);
				came_from[next.GetToNode().pos] = current.pos;
				visited.push_back(next.to);
			}

		}
	}
	return path;
}

GBFS::~GBFS()
{
}
