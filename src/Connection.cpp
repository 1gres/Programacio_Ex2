#include "Connection.h"


Connection::Connection(Node _from, Node _to, float _cost)
{
	from = _from;
	to = _to;
	cost = _cost;
}


Connection::~Connection()
{
}


float Connection::GetCost() {
	return cost;
}

//Returns the node that this connection came from
Node Connection::GetFromNode() {
	return from;
}

//Returns the node that this connection leads to
Node Connection::GetToNode() {
	return to;
}