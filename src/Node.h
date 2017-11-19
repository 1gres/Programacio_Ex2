#pragma once
#include <vector>
#include "Vector2D.h"
#include <tuple> 


class Node
{
public:
	Vector2D pos;
	Node();
	Node(float _x, float _y);
	Node(Vector2D v);
	bool visited;
	inline float Length() const {
		return (float)sqrt(pos.x * pos.x + pos.y * pos.y);
	}

	inline bool operator<(const Node& rhs) const {
		return std::tie(pos.x, pos.y) < std::tie(rhs.pos.x, rhs.pos.y);
	}

	inline bool operator<=(const Node& rhs) const {
		return !(std::tie(pos.x, pos.y) <  std::tie(rhs.pos.x, rhs.pos.y));
	}

	inline bool operator>(const Node& rhs) const {
		return std::tie(pos.x, pos.y) <  std::tie(rhs.pos.x, rhs.pos.y);
	}

	inline bool operator>=(const Node& rhs) const {
		return !(std::tie(pos.x, pos.y) <  std::tie(rhs.pos.x, rhs.pos.y));
	}
	~Node();
	
};

// Necessary to use unordered_maps
namespace std {
	template<>
	struct hash<Node> {
		size_t operator()(const Node& n) const {
			return std::hash<float>()(n.Length());
		}
	};
}



