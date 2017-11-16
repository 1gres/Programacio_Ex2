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

Node::Node(Vector2D v) {
	pos.x = v.x;
	pos.y = v.y;
}

Node::~Node()
{
}

