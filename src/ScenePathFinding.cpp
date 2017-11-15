#include "ScenePathFinding.h"
#include "Node.h"
#include "Connection.h"
#include "BFS.h"


using namespace std;

ScenePathFinding::ScenePathFinding()
{
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);


	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!isValidCell(rand_cell)) 
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3)) 
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	
	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;

	//BFS default algorithm
	if (tipusAlgoritme == 0) {
		Node agentPosition(0,0);

		agentPosition.pos = pix2cell(agents[0]->getPosition());

		Node coinPos(0,0);
		coinPos.pos.x = coinPosition.x;
		coinPos.pos.y = coinPosition.y;
		
		std::vector<Node> myPath = bfsObject.BFSSearch(graph, agentPosition, coinPos);
		std::vector<Vector2D> pathConverted;
		
		for (unsigned int i = 0; i < myPath.size(); i++) {
			pathConverted.push_back(myPath[i].pos);
		}

		for (unsigned int i = 0; i < pathConverted.size(); i++) {
			
			path.points.push_back(cell2pix(pathConverted[i]));
		}
		
	}
}

ScenePathFinding::~ScenePathFinding()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFinding::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (isValidCell(cell))
			{
				if (path.points.size() > 0)
					if (path.points[path.points.size() - 1] == cell2pix(cell))
						break;

				path.points.push_back(cell2pix(cell));
			}
		}
		break;
	case SDL_SCANCODE_A:
		//BFS
		tipusAlgoritme = 0;
		//cridar funcions del algoritme
		break;

	case SDL_SCANCODE_S:
		//Dijkstra
		tipusAlgoritme = 1;
		//cridar funcions del algoritme
		break;
	case SDL_SCANCODE_D:
		//GBFS
		tipusAlgoritme = 2;
		//cridar funcions del algoritme
		break;
	case SDL_SCANCODE_F:
		//A*
		tipusAlgoritme = 3;
		//cridar funcions del algoritme
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
					path.points.clear();
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0,0));
					// if we have arrived to the coin, replace it ina random cell!
					if (pix2cell(agents[0]->getPosition()) == coinPosition)
					{
						coinPosition = Vector2D(-1, -1);
						while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition()))<3))
							coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
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
		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		agents[0]->update(steering_force, dtime, event);
	} 
	else
	{
		agents[0]->update(Vector2D(0,0), dtime, event);
	}
}

void ScenePathFinding::draw()
{
	drawMaze();
	drawCoin();


	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* ScenePathFinding::getTitle()
{
	return "SDL Steering Behaviors :: PathFinding1 Demo";
}

void ScenePathFinding::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
	}
}

void ScenePathFinding::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void ScenePathFinding::createGraph() {
	

	//40 celdas de width y 24 de height
	//el total de todas las conexiones da como resultado: 2486
	for (int i = 0; i < num_cell_x; i++)
	{
		//std::cout << i << std::endl;
		for (int j = 0; j < num_cell_y; j++)
		{

			if (terrain[i][j] != 0) {

				Node from((float)i, (float)j);

				//conexiones derecha (banda)
				if (((i == 39) && (j >= 10 && j <= 12))) {
					Node toRight((float)0, (float)(j));
					Connection conRight(from, toRight, 1.f);
					graph.AddConnection(conRight);

					Node toLeft((float)i - 1, (float)(j));
					Connection conLeft(from, toLeft, 1.f);
					graph.AddConnection(conLeft);

					if (j == 10) {
						Node toDown((float)i, (float)(j + 1));
						Connection conDown(from, toDown, 1.f);
						graph.AddConnection(conDown);
					}
					else if (j == 11) {
						Node toUp((float)i, (float)(j - 1));
						Connection conUp(from, toUp, 1.f);
						graph.AddConnection(conUp);

						Node toDown((float)i, (float)(j + 1));
						Connection conDown(from, toDown, 1.f);
						graph.AddConnection(conDown);
					}
					else if (j == 12) {
						Node toUp((float)i, (float)(j - 1));
						Connection conUp(from, toUp, 1.f);
						graph.AddConnection(conUp);
					}

				}

				//conexiones izquierda (banda)
				if (((i == 0) && (j >= 10 && j <= 12))) {
					Node toLeft((float)39, (float)(j));
					Connection conLeft(from, toLeft, 1.f);
					graph.AddConnection(conLeft);

					Node toRight((float)i + 1, (float)(j));
					Connection conRight(from, toRight, 1.f);
					graph.AddConnection(conRight);

					if (j == 10) {
						Node toDown((float)i, (float)(j + 1));
						Connection conDown(from, toDown, 1.f);
						graph.AddConnection(conDown);
					}
					else if (j == 11) {
						Node toUp((float)i, (float)(j - 1));
						Connection conUp(from, toUp, 1.f);
						graph.AddConnection(conUp);

						Node toDown((float)i, (float)(j + 1));
						Connection conDown(from, toDown, 1.f);
						graph.AddConnection(conDown);
					}
					else if (j == 12) {
						Node toUp((float)i, (float)(j - 1));
						Connection conUp(from, toUp, 1.f);
						graph.AddConnection(conUp);
					}
				}

				//mirar vecinos de la derecha teniendo en cuenta paredes laterales a excepci�n de los tres nodos laterales derechos
				if (((i > 0 && i < num_cell_x - 2) && (j > 0 && j < num_cell_y)) || ((i < num_cell_x - 1) && (j >= 10 && j <= 12) && (i > 0))) {
					if (terrain[i + 1][j] != 0) {
						Node to((float)i + 1, (float)(j));
						Connection con(from, to, 1.f);
						graph.AddConnection(con);
						//std::cout << from.pos.x << " to " << to.pos.x << "; " << std::endl;
					}
				}

				//mirar vecinos de la izquierda teniendo en cuenta paredes laterales a excepci�n de los tres nodos laterales izquierdos
				if (((i > 1 && i < num_cell_x - 1) && (j > 0 && j < num_cell_y)) || ((i >= 1 && i < num_cell_x - 1) && (j >= 10 && j <= 12))) {
					if (terrain[i - 1][j] != 0) {
						Node to((float)i - 1, (float)(j));
						Connection con(from, to, 1.f);
						graph.AddConnection(con);
						//std::cout << from.pos.x << " to " << to.pos.x << "; " << std::endl;
					}
				}

				//mirar los vecinos de arriba
				if (((i > 0 && i < num_cell_x - 1) && (j > 1 && j < num_cell_y - 1))) {
					if (terrain[i][j - 1] != 0) {
						Node to((float)i, (float)(j - 1));
						Connection con(from, to, 1.f);
						graph.AddConnection(con);
						//std::cout << from.pos.y << " to " << to.pos.y << "; " << std::endl;
					}
				}

				//mirar los vecinos de abajo
				if (((i > 0 && i < num_cell_x - 1) && (j > 0 && j < num_cell_y - 2))) {
					if (terrain[i][j + 1] != 0) {
						Node to((float)i, (float)(j + 1));
						Connection con(from, to, 1.f);
						graph.AddConnection(con);
						//std::cout << from.pos.y << " to " << to.pos.y << "; " << std::endl;
					}
				}

			}
		}
	}
}

void ScenePathFinding::initMaze()
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
			Vector2D cell_center ((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
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

bool ScenePathFinding::loadTextures(char* filename_bg, char* filename_coin)
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

	return true;
}

Vector2D ScenePathFinding::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D ScenePathFinding::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x/CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool ScenePathFinding::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()) )
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}

