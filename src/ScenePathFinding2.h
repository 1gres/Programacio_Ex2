#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "AStar.h"
#include "Graph.h"

class ScenePathFinding2 :
	public Scene
{
public:
	ScenePathFinding2();
	~ScenePathFinding2();
	void update(float dtime, SDL_Event *event);
	void teleportBridge();
	void draw();
	const char* getTitle();
private:
	Graph graph;
	AStar aStar;
	void printMaxMinAverageNodesExplorats(int nodesExplorats);
	int random();
	int randomObjectius(int num);
	int numCoins;
	int numObjectius;
	int maxNodesExplorats;
	int minNodesExplorats;
	int averageNodesExplorats;
	std::vector<float> sizesVisited;
	std::vector<Vector2D> myPath;
	std::vector<Agent*> agents;
	std::vector<Vector2D> coinPositions;
	std::vector<std::pair<float, Vector2D>> values;
	std::vector<Vector2D> goals;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin(int posArray);
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	SDL_Texture *coin_texture2;
	void initMaze();
	bool loadTextures(char* filename_bg, char* filename_coin, char* filename_coin2);
	std::vector< std::vector<int> > terrain;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	void createGraph();

};
