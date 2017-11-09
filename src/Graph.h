#pragma once
#include <vector>
#include "Node.h"
#include "Connection.h"

class Graph
{
public:
	Graph();
	~Graph();

	//funcio que permet accedir a la llista  i retornar les conexions de un node
	
	std::vector<Connection> GetConnections(Node from);
	// Alternativa 
	//en lugar de retornar el vector con objetos connection, devolver directamente un vector con cada nodo TO del parametro FROM
	//std::vector<Node> GetConnections(Node from);

	//Add new connection
	void AddConnection(Connection c);

	

private:
	std::vector<Connection> graph;
};
