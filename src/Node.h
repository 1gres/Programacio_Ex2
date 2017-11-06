#pragma once
#include <vector>
#include "Vector2D.h"
#include "Connection.h"

class Node
{
public:
	Node();
	Node(float _x, float _y);
	~Node();
	Vector2D pos;

	//Add new connection this node to other node
	void AddConnection(Connection c);

	//Get connections of node
	std::vector<Connection> GetConnections();

private:
	//connections of this node to other nodes
	std::vector<Connection> connections;
};