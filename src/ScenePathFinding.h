#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Graph.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "GBFS.h"
#include "AStar.h"
#include <iostream>
#include "Node.h"
#include <time.h> 


class ScenePathFinding :
	public Scene
{
public:
	ScenePathFinding(int _tipusAlgoritme);
	~ScenePathFinding();
	void update(float dtime, SDL_Event *event);
	void teleportBridge();
	void draw();
	const char* getTitle();
	float RandomFloat(float a, float b);
private:
	Graph graph;
	BFS bfs;
	Dijkstra dijkstra;
	GBFS gbfs;
	AStar aStar;
	void printMaxMinAverageNodesExplorats(int nodesExplorats);
	int maxNodesExplorats;
	int minNodesExplorats;
	int averageNodesExplorats;
	int sumAverageNodesExplorats;
	std::vector<Vector2D> myPath;
	int tipusAlgoritme;
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin();
	void createGraph();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	void initMaze();
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector< std::vector<int> > terrain;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);

};
