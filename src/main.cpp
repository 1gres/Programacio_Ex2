#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "ScenePathFinding.h"
#include "ScenePathFinding2.h"
#include "ScenePathFinding3.h"

#define FRAMES_PER_SEC 30

using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;
	int this_tick = 0;
	int next_tick = 1000/FRAMES_PER_SEC;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new ScenePathFinding(1);
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		this_tick = SDL_GetTicks();
		/*if (this_tick < next_tick)
		{
			SDL_Delay(next_tick - this_tick);
		}*/
		next_tick = this_tick + (1000 / FRAMES_PER_SEC);

		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:

			if (event.key.keysym.scancode == SDL_SCANCODE_0)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding(0);
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding(1);
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_Q)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding(1);
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_W)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding(2);
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_E)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding(3);
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_R)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding(4);
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding2;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFinding3;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_P) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}