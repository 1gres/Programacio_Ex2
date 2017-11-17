#pragma once
#include <iostream>
#include <vector>
# include "Graph.h"
# include "Node.h"
#include <queue>
#include <unordered_map>
#include <time.h> 
#include "Vector2D.h" 
#include <functional>

template<typename T, typename priority_t>
struct MyPriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	inline T get() {
		T best_item = elements.top().second;
		elements.pop(); // pop everytime we acces next element
		return best_item;
	}
};