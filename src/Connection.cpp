#include "Connection.h"


Connection::Connection(Node _from, Node _to, float _cost)
{
	from = Node(_from.pos.x, _from.pos.y);
	to = Node(_to.pos.x, _to.pos.y);
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