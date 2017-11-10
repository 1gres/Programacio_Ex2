#include "Node.h"

Node::Node()
{
	visited = false;
	pos.x = 0;
	pos.y = 0;
}

Node::Node(float _x, float _y)
{
	visited = false;
	pos.x = _x;
	pos.y = _y;
}


Node::~Node()
{
}

