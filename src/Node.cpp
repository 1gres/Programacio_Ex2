#include "Node.h"



Node::Node()
{
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
