#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}

std::vector<Connection> Graph::GetConnections(Node from) {
	return from.GetConnections();
	
}

void Graph::AddConnection(Connection c) {
	graph.push_back(c);
}
