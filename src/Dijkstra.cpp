#include "Dijkstra.h"

Dijkstra::Dijkstra() {

}

int Dijkstra::random() {
	return (std::rand() % 3) + 1;
}

std::vector<Vector2D> Dijkstra::DijkstraSearch(Graph graph, Node root, Node goal)
{
	
	MyPriorityQueue<Vector2D, float> frontier;

	Node current(0, 0);
	Node from(0, 0), to(0, 0);
	Connection next(from, to, 1);

	std::vector<Connection> connections;

	frontier.put(root.pos, 0.f);

	std::unordered_map<Vector2D, Vector2D> came_from;
	came_from[root.pos] = NULL;

	std::unordered_map<Vector2D, float> cost_so_far;
	cost_so_far[root.pos] = 0.f;

	std::vector<Vector2D> path;

	float new_cost, priority;
	int cost = 0;
	std::srand(time(NULL));
	visited.clear();
	costos.clear();

	while (!frontier.empty())
	{
		current = frontier.get();

		if (current.pos == goal.pos) {

			//reconstruct path
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
			//cost = next.GetCost(); se laguea mucho....por eso usamos random
			cost = random();
			new_cost = cost_so_far[current.pos] + cost;
			costos.push_back(cost);
			for (unsigned int j = 0; j < cost_so_far.size(); j++) {
				if (cost_so_far.find(next.GetToNode().pos) != cost_so_far.end()) {
					if (new_cost > cost_so_far[next.GetToNode().pos]) {
						next.to.visited = true;
					}
					
				}
				else {
					next.to.visited = false;
				}
			}
			if (!next.to.visited) {
				cost_so_far[next.GetToNode().pos] = new_cost;
				priority = new_cost;
				frontier.put(next.GetToNode().pos, priority);
				came_from[next.GetToNode().pos] = current.pos;
				visited.push_back(next.to);
			}

		}
	}
	return path;
}


Dijkstra::~Dijkstra()
{
}