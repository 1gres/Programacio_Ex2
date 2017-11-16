#include "Dijkstra.h"

Dijkstra::Dijkstra() {

}

std::vector<Vector2D> Dijkstra::DijkstraSearch(Graph graph, Node root, Node goal)
{

	std::queue<Node> frontier;

	Node current(0, 0);
	Node from(0, 0), to(0, 0);
	Connection next(from, to, 1);

	std::vector<Connection> connections;

	frontier.push(root);

	std::unordered_map<Vector2D, Vector2D> came_from;
	came_from[root.pos] = NULL;

	bool visited;
	std::vector<Vector2D> path;

	while (!frontier.empty())
	{
		current = frontier.front();
		frontier.pop();
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
				if (came_from.find(next.to.pos) != came_from.end()) {
					visited = true;
				}
			}
			if (!visited) {
				frontier.push(next.to);
				came_from[next.to.pos] = current.pos;
			}

		}
	}
}


Dijkstra::~Dijkstra()
{
}