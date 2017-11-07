#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}

/*
std::vector<Connection> Graph::GetConnections(Node from) {
	std::vector<Connection> connectionsNode;

	//falta esta parte.....
	return connectionsNode;
}*/

void Graph::AddConnection(Connection c) {
	graph.push_back(c);
}


