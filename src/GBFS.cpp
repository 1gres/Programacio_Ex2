#include "GBFS.h"


GBFS::GBFS() {

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

	bool visited;
	std::vector<Vector2D> path;

	float priority;

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
			visited = false;
			next = connections[i];

			for (unsigned int j = 0; j < came_from.size(); j++) {
				
				if (came_from.find(next.GetToNode().pos) != came_from.end()) {
					visited = true;
				}
			}

			if (!visited) {
				priority = Heuristic(goal.pos, next.GetToNode().pos);
				frontier.put(next.GetToNode().pos, priority);
				came_from[next.GetToNode().pos] = current.pos;
			}

		}
	}
}

GBFS::~GBFS()
{
}
