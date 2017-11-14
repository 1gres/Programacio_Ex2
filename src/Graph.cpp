#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}


std::vector<Connection> Graph::GetConnections(Node from) {

	//guardar todas las conexiones de from i retornarles
	std::vector<Connection> connections;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].GetFromNode().pos == from.pos) {
			connections.push_back(graph[i]);
			if (connections.size()>=4) {
				break;
			}
			/*std::cout << "from x: " << connections[i].from.pos.x << "\nfrom y: " << connections[i].from.pos.y << std::endl;
			std::cout << "to x: " << connections[i].to.pos.x << "\nto: " << connections[i].to.pos.y << std::endl;*/
		}
	}
	
	return connections;

	//alternativa..en lugar de retornar el vector con objetos connection, devolver directamente un vector con cada nodo TO del parametro FROM
	/*
	//guardar todas las conexiones de from
	std::vector<Node> neighbors;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].GetFromNode().pos == from.pos) {
			neighbors.push_back(graph[i].GetToNode());
		}
	}
	
	return connectionsNode;
	*/
}

void Graph::AddConnection(Connection c) {
	graph.push_back(c);
}


