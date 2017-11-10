#include "BFS.h"

/*
std::vector<Node> BFS::BFS(Graph graph, Node root, Node goal)
{
	
	int valorCasella = 0;
	int contadorCaselles = 1;

		std::queue<Node> frontier;
		Node current(0, 0), next(0, 0);

		frontier.push(root);
		std::cout << "Node root x: " << root.pos.x << "\nNode root y: " << root.pos.y << std::endl;

		root.visited = true;

		while (!frontier.empty() && current.pos != goal.pos)
		{
			current = frontier.front();
			frontier.pop();
			
			for (int i = 0; i < graph.GetConnections(current).size(); i++) {
				if (current.visited == false) {
					current.visited = true;
					//current.visited = contadorCaselles;
					contadorCaselles++;
				}
			}
			valorCasella++;
			//current = valor casella;


		}
	


		/*
		asignar la posicio del agent al valor 0
		int contadorselles = 1;

		Interacció entre les posicions.

		Dreta

		if (current.visited = false)
		 {
			asisgnar el valor de contradorcaselles a la casella;
			contadorcaselles ++;
		 }

		 Esquerra

		 if (current.visited = false)
		 {
		 asisgnar el valor de contradorcaselles a la casella;
		 contadorcaselles ++;
		 }

		 Adalt

		 if (current.visited = false)
		 {
		 asisgnar el valor de contradorcaselles a la casella;
		 contadorcaselles ++;
		 }
		 
		 Abaix

		 if (current.visited = false)
		 {
		 asisgnar el valor de contradorcaselles a la casella;
		 contadorcaselles ++;
		 }

		 valorposicioagent++;

		
	
}*/


BFS::~BFS()
{
}
