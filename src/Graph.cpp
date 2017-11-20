#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}

std::vector<Connection> Graph::GetGraph() {
	return graph;
}

std::vector<Connection> Graph::GetConnections(Node from) {

	//guardar todas las conexiones de from i retornarles
	std::vector<Connection> connections;
	for (unsigned int i = 0; i < graph.size(); i++) {
		if (graph[i].GetFromNode().pos == from.pos) {
			connections.push_back(graph[i]);
			if (connections.size()>=4) {
				break;
			}
		}
	}
	

	return connections;
}

void Graph::AddConnection(Connection c) {
	graph.push_back(c);
}


