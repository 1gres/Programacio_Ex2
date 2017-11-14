#pragma once
#include "Node.h"

class Connection
{
public:
	Node from, to;

	float cost;
	Connection(Node _from, Node _to, float _cost);
	~Connection();

	//Returns the non-negative cost of the connection
	float GetCost();

	//Returns the node that this connection came from
	Node GetFromNode();

	//Returns the node that this connection leads to
	Node GetToNode();
private:
	
};

