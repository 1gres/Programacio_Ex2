#include "ScenePathFinding2.h"
#include "Node.h"
#include "Connection.h"
#include "BFS.h"


using namespace std;

ScenePathFinding2::ScenePathFinding2()
{
	system("cls");
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/maze.png", "../res/coin.png", "../res/coin2.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	std::cout << "Escribe un numero maximo para generar objetivos (limitado a 10): ";
	std::cin >> numObjectius;
	if (numObjectius > 10) numObjectius = 10;
	numCoins = randomObjectius(numObjectius);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	
	// set the coin in a random cell (but at least 3 cells far from the agent)
	for (int i = 0; i < numCoins; i++) {
		Vector2D pos(-1, -1);
		while ((!isValidCell(pos)) || (Vector2D::Distance(pos, pix2cell(agents[0]->getPosition()))<3))
			pos = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
		coinPositions.push_back(pos);

	}

	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;


	Node agentPosition(0, 0);

	agentPosition.pos = pix2cell(agents[0]->getPosition());

	maxNodesExplorats = -1;
	minNodesExplorats = 9999;
	averageNodesExplorats = 9999;

	system("cls");

	for (unsigned int i = 0; i < coinPositions.size()-1; i++) {
		values.push_back(std::make_pair(aStar.Heuristic(agentPosition.pos, coinPositions[i]), coinPositions[i]));
	}
	std::sort(values.begin(), values.end());

	goals.push_back(agentPosition.pos);
	for (unsigned int i = 0; i < values.size(); i++) {
		goals.push_back(values[i].second);
	}
	goals.push_back(coinPositions[coinPositions.size() - 1]);

	//A* amb varis objectius
	for (unsigned int i = 0; i < goals.size()-1; i++) {
		myPath = aStar.AStarSearch(graph, goals[i], goals[i + 1],true);
		for (unsigned int i = 0; i <myPath.size(); i++) {
			path.points.push_back(cell2pix(myPath[i]));
		}
		printMaxMinAverageNodesExplorats(aStar.visited.size());
	}
}

int ScenePathFinding2::random() {
	return (std::rand() % 5) + 1;
}

int ScenePathFinding2::randomObjectius(int num) {
	int ran = (std::rand() % num) + 1;
	if (ran == 1) {
		ran = 2;
	}
	return ran;
}


void ScenePathFinding2::printMaxMinAverageNodesExplorats(int nodesExplorats) {

	if (nodesExplorats >= maxNodesExplorats) {
		maxNodesExplorats = nodesExplorats;
	}
	if (nodesExplorats <= minNodesExplorats) {
		minNodesExplorats = nodesExplorats;
	}
	sizesVisited.push_back(nodesExplorats);
	int sum = 0;
	for (int i = 0; i < sizesVisited.size(); i++) {
		sum += sizesVisited[i];
	}
	averageNodesExplorats = sum / sizesVisited.size();

	std::cout << "\r" << "Current: " << nodesExplorats << ",   Max: " << maxNodesExplorats << ",   Min: " << minNodesExplorats << ",   Average: " << averageNodesExplorats << "               ";

}

ScenePathFinding2::~ScenePathFinding2()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);
	if (coin_texture2)
		SDL_DestroyTexture(coin_texture2);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFinding2::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
			draw_grid = !draw_grid;
			break;
		}
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:

		break;
	default:
		break;
	}
	if ((currentTargetIndex == -1) && (path.points.size()>0))
		currentTargetIndex = 0;

	if (currentTargetIndex >= 0)
	{
		float dist = Vector2D::Distance(agents[0]->getPosition(), path.points[currentTargetIndex]);
		if (dist < path.ARRIVAL_DISTANCE)
		{
			if (currentTargetIndex == path.points.size() - 1)
			{
				if (dist < 3)
				{
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0, 0));
					// if we have arrived to the coin, replace it ina random cell!
					if (pix2cell(agents[0]->getPosition()) == coinPositions[coinPositions.size()-1])
					{
						coinPositions.clear();
						values.clear();
						goals.clear();
						aStar.costos.clear();
						aStar.visited.clear();
						
						numCoins = randomObjectius(numObjectius);

						for (int i = 0; i < numCoins; i++) {
							Vector2D pos(-1, -1);
							while ((!isValidCell(pos)) || (Vector2D::Distance(pos, pix2cell(agents[0]->getPosition()))<3)) 
								pos = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
							coinPositions.push_back(pos);
						}

						agents[0]->setPosition(path.points.back());

						path.points.clear();

						Node agentPosition(0, 0);

						agentPosition.pos = pix2cell(agents[0]->getPosition());

						for (unsigned int i = 0; i < coinPositions.size() - 1; i++) {
							values.push_back(std::make_pair(aStar.Heuristic(agentPosition.pos, coinPositions[i]), coinPositions[i]));
						}
						std::sort(values.begin(), values.end());

						goals.push_back(agentPosition.pos);
						for (unsigned int i = 0; i < values.size(); i++) {
							goals.push_back(values[i].second);
						}
						goals.push_back(coinPositions[coinPositions.size() - 1]);

						//A* amb varis objectius
						for (unsigned int i = 0; i < goals.size() - 1; i++) {
							myPath = aStar.AStarSearch(graph, goals[i], goals[i + 1],true);
							for (unsigned int i = 0; i <myPath.size(); i++) {
								path.points.push_back(cell2pix(myPath[i]));
							}
							printMaxMinAverageNodesExplorats(aStar.visited.size());
						}
						
					
					}
				}
				else
				{
					Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], currentTarget, path.ARRIVAL_DISTANCE, dtime);
					agents[0]->update(steering_force, dtime, event);
				}
				return;
			}
			currentTargetIndex++;
		}

		currentTarget = path.points[currentTargetIndex];
		teleportBridge();

		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		agents[0]->update(steering_force, dtime, event);
	}
	else
	{
		agents[0]->update(Vector2D(0, 0), dtime, event);
	}
}

void ScenePathFinding2::draw()
{
	drawMaze();
	
	for (int i = 0; i < coinPositions.size(); i++) {
		drawCoin(i);
	}

	Vector2D agentPos;
	agentPos = pix2cell(agents[0]->getPosition());

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}

		Vector2D printFrontier;
		for (int i = 0; i < aStar.visited.size(); i = i++)
		{
			printFrontier = cell2pix(aStar.visited[i].pos);
			if (aStar.costos[i] == 1) {
				draw_circle(TheApp::Instance()->getRenderer(), (int)printFrontier.x, (int)printFrontier.y, 5, 255, 0, 0, 255);
			}
			if (aStar.costos[i] == 2) {
				draw_circle(TheApp::Instance()->getRenderer(), (int)printFrontier.x, (int)printFrontier.y, 5, 0, 255, 0, 255);
			}
			if (aStar.costos[i] == 3) {
				draw_circle(TheApp::Instance()->getRenderer(), (int)printFrontier.x, (int)printFrontier.y, 5, 0, 0, 255, 255);
			}
			if (aStar.costos[i] == 4) {
				draw_circle(TheApp::Instance()->getRenderer(), (int)printFrontier.x, (int)printFrontier.y, 5, 255, 255, 0, 255);
			}
			if (aStar.costos[i] == 5) {
				draw_circle(TheApp::Instance()->getRenderer(), (int)printFrontier.x, (int)printFrontier.y, 5, 255, 0, 255, 255);
			}
		}
		

	}

	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);

		if (i > 0 && abs(path.points[i - 1].x - path.points[i].x) < 100) {
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
		}
	}

	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* ScenePathFinding2::getTitle()
{
	return "Exercici 2";
}

void ScenePathFinding2::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL);
	}
}

void ScenePathFinding2::drawCoin(int posArray)
{
	Vector2D coin_coords;
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect;

	if (posArray == coinPositions.size() - 1) {
		coin_coords = cell2pix(coinPositions[coinPositions.size() - 1]);
		dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}
	else {
		coin_coords = cell2pix(coinPositions[posArray]);
		dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture2, NULL, &dstrect);
	}
		
		
	
}

void ScenePathFinding2::createGraph() {
	//40 celdas de width y 24 de height
	//el total de todas las conexiones da como resultado: 2486
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{

			//codigo abreviado y optimizado de la versión anterior
			//if no wall
			if (terrain[i][j] != 0) {
				Node from((float)i, (float)j);
				Node to;
				Connection con(from, to, 1);

				//isValidCell() es per saber si exiteix la casella que busquem

				//verificando por derecha
				to.pos.x = (float)i + 1; to.pos.y = (float)j;

				//Mirar derecha(que el to.pos con el nuevo valor en x e y sean validos) y que no haya muro
				if (isValidCell(to.pos) && terrain[i + 1][j] != 0 && !((i == 39 || i == 0) && (j >= 10 && j <= 12))) {
					con = { from, to, random() };
					graph.AddConnection(con);
				}

				//verificando izquierda
				to.pos.x = (float)i - 1; to.pos.y = (float)j;

				//Mirar izquierda(que el to.pos con el nuevo valor en x e y sean validos) y que no haya muro
				if (isValidCell(to.pos) && terrain[i - 1][j] != 0 && !((i == 39 || i == 0) && (j >= 10 && j <= 12))) {
					con = { from, to, random() };
					graph.AddConnection(con);
				}

				//verificando por arriba
				to.pos.x = (float)i; to.pos.y = (float)j - 1;

				//Mirar arriba(que el to.pos con el nuevo valor en x e y sean validos) y que no haya muro
				if (isValidCell(to.pos) && terrain[i][j - 1] != 0 && !((i == 39 || i == 0) && (j >= 10 && j <= 12))) {
					con = { from, to, random() };
					graph.AddConnection(con);
				}

				//verificando por abajo
				to.pos.x = (float)i; to.pos.y = (float)j + 1;

				//Mirar abajo(que el to.pos con el nuevo valor en x e y sean validos) y que no haya muro
				if (isValidCell(to.pos) && terrain[i][j + 1] != 0 && !((i == 39 || i == 0) && (j >= 10 && j <= 12))) {
					con = { from, to, random() };
					graph.AddConnection(con);
				}

				//conexiones derecha (banda)
				if (((i == 39) && (j >= 10 && j <= 12))) {
					to.pos.x = (float)0; to.pos.y = (float)j;
					con = { from, to, random() };
					graph.AddConnection(con);

					to.pos.x = (float)i - 1; to.pos.y = (float)j;
					con = { from, to, random() };
					graph.AddConnection(con);

					if (j == 10) {
						to.pos.x = (float)i; to.pos.y = (float)j + 1;
						con = { from, to, random() };
						graph.AddConnection(con);
					}
					else if (j == 11) {
						to.pos.x = (float)i; to.pos.y = (float)j - 1;
						con = { from, to, random() };
						graph.AddConnection(con);

						to.pos.x = (float)i; to.pos.y = (float)j + 1;
						con = { from, to, random() };
						graph.AddConnection(con);
					}
					else if (j == 12) {
						to.pos.x = (float)i; to.pos.y = (float)j - 1;
						con = { from, to, random() };
						graph.AddConnection(con);
					}

				}

				//conexiones izquierda (banda)
				if (((i == 0) && (j >= 10 && j <= 12))) {
					to.pos.x = (float)i + 1; to.pos.y = (float)j;
					con = { from, to, random() };
					graph.AddConnection(con);

					to.pos.x = (float)39; to.pos.y = (float)j;
					con = { from, to, random() };
					graph.AddConnection(con);

					if (j == 10) {
						to.pos.x = (float)i; to.pos.y = (float)j + 1;
						con = { from, to, random() };
						graph.AddConnection(con);
					}
					else if (j == 11) {
						to.pos.x = (float)i; to.pos.y = (float)j - 1;
						con = { from, to, random() };
						graph.AddConnection(con);

						to.pos.x = (float)i; to.pos.y = (float)j + 1;
						con = { from, to, random() };
						graph.AddConnection(con);
					}
					else if (j == 12) {
						to.pos.x = (float)i; to.pos.y = (float)j - 1;
						con = { from, to, random() };
						graph.AddConnection(con);
					}
				}
			}
		}
	}
}

void ScenePathFinding2::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 608, 32, 64, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 608, 512, 64, 224 };
	maze_rects.push_back(rect);
	rect = { 0,32,32,288 };
	maze_rects.push_back(rect);
	rect = { 0,416,32,320 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,288 };
	maze_rects.push_back(rect);
	rect = { 1248,416,32,320 };
	maze_rects.push_back(rect);
	rect = { 128,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 288,128,96,32 };
	maze_rects.push_back(rect);
	rect = { 480,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 736,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 896,128,96,32 };
	maze_rects.push_back(rect);
	rect = { 1088,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 128,256,64,32 };
	maze_rects.push_back(rect);
	rect = { 288,256,96,32 };
	maze_rects.push_back(rect);
	rect = { 480, 256, 320, 32 };
	maze_rects.push_back(rect);
	rect = { 608, 224, 64, 32 };
	maze_rects.push_back(rect);
	rect = { 896,256,96,32 };
	maze_rects.push_back(rect);
	rect = { 1088,256,64,32 };
	maze_rects.push_back(rect);
	rect = { 128,384,32,256 };
	maze_rects.push_back(rect);
	rect = { 160,512,352,32 };
	maze_rects.push_back(rect);
	rect = { 1120,384,32,256 };
	maze_rects.push_back(rect);
	rect = { 768,512,352,32 };
	maze_rects.push_back(rect);
	rect = { 256,640,32,96 };
	maze_rects.push_back(rect);
	rect = { 992,640,32,96 };
	maze_rects.push_back(rect);
	rect = { 384,544,32,96 };
	maze_rects.push_back(rect);
	rect = { 480,704,32,32 };
	maze_rects.push_back(rect);
	rect = { 768,704,32,32 };
	maze_rects.push_back(rect);
	rect = { 864,544,32,96 };
	maze_rects.push_back(rect);
	rect = { 320,288,32,128 };
	maze_rects.push_back(rect);
	rect = { 352,384,224,32 };
	maze_rects.push_back(rect);
	rect = { 704,384,224,32 };
	maze_rects.push_back(rect);
	rect = { 928,288,32,128 };
	maze_rects.push_back(rect);

	// Initialize the terrain matrix (for each cell a zero value indicates it's a wall)

	// (1st) initialize all cells to 1 by default
	for (int i = 0; i < num_cell_x; i++)
	{
		vector<int> terrain_col(num_cell_y, 1);
		terrain.push_back(terrain_col);
	}
	// (2nd) set to zero all cells that belong to a wall
	int offset = CELL_SIZE / 2;
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			Vector2D cell_center((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
			for (unsigned int b = 0; b < maze_rects.size(); b++)
			{
				if (Vector2DUtils::IsInsideRect(cell_center, (float)maze_rects[b].x, (float)maze_rects[b].y, (float)maze_rects[b].w, (float)maze_rects[b].h))
				{
					terrain[i][j] = 0;
					break;
				}
			}

		}
	}

	createGraph();

}

void ScenePathFinding2::teleportBridge() {

	if (currentTarget == cell2pix(Vector2D{ 0,10 })) {
		if (path.points[currentTargetIndex - 1] == cell2pix(Vector2D{ 39,10 }))
			agents[0]->setPosition(cell2pix(Vector2D{ 0,10 }));
	}
	else if (currentTarget == cell2pix(Vector2D{ 0,11 })) {
		if (path.points[currentTargetIndex - 1] == cell2pix(Vector2D{ 39,11 }))
			agents[0]->setPosition(cell2pix(Vector2D{ 0,11 }));
	}
	else if (currentTarget == cell2pix(Vector2D{ 0,12 })) {
		if (path.points[currentTargetIndex - 1] == cell2pix(Vector2D{ 39,12 }))
			agents[0]->setPosition(cell2pix(Vector2D{ 0,12 }));
	}
	else if (currentTarget == cell2pix(Vector2D{ 39,10 })) {
		if (path.points[currentTargetIndex - 1] == cell2pix(Vector2D{ 0,10 }))
			agents[0]->setPosition(cell2pix(Vector2D{ 39,10 }));
	}
	else if (currentTarget == cell2pix(Vector2D{ 39,11 })) {
		if (path.points[currentTargetIndex - 1] == cell2pix(Vector2D{ 0,11 }))
			agents[0]->setPosition(cell2pix(Vector2D{ 39,11 }));
	}
	else if (currentTarget == cell2pix(Vector2D{ 39,12 })) {
		if (path.points[currentTargetIndex - 1] == cell2pix(Vector2D{ 0,12 }))
			agents[0]->setPosition(cell2pix(Vector2D{ 39,12 }));
	}
}

bool ScenePathFinding2::loadTextures(char* filename_bg, char* filename_coin, char* filename_coin2)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);
	image = IMG_Load(filename_coin2);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture2 = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D ScenePathFinding2::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D ScenePathFinding2::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool ScenePathFinding2::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}

