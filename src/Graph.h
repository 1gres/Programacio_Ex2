#pragma once
#include <vector>
#include "Connection.h"

class Graph
{
public:
	Graph();
	~Graph();
	
	//funcio que permet accedir a la llista  i retornar les conexions de un node
	// seria algu aixi: vector<Connection> getConnectionsFrom(Node from);
	std::vector<Connection> GetConnections(Node from);

	//Add new connection
	void AddConnection(Connection c);

private:
	std::vector<Connection> graph;
	
};
