#pragma once
#include "Node.h"

class Connection
{
public:

	Node from, to;
	float cost;

	Connection(Node, Node, float);
	~Connection();

	//Returns the non-negative cost of the connection
	float Connection::GetCost() { return cost; }

	//Returns the node that this connection came from
	Node GetFromNode() { return from; }

	//Returns the node that this connection leads to
	Node GetToNode() { return to; }

};

