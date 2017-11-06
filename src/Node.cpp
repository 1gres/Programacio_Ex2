#include "Node.h"


Node::Node()
{
	pos.x = 0;
	pos.y = 0;
}

Node::Node(float _x, float _y)
{
	pos.x = _x;
	pos.y = _y;
}


Node::~Node()
{
}

void Node::AddConnection(Connection c) {
	connections.push_back(c);
}


std::vector<Connection> Node::GetConnections() {
	return connections;
}
