#pragma once
#include <vector>
#include "Vector2D.h"

class Node
{
public:
	Vector2D pos;
	bool visited;
	Node();
	Node(float _x, float _y);
	~Node();
	
};

