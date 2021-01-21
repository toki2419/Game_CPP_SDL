// SDLGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
BaseObject g_background;
bool InitData() 
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Game CPP SDL 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			if (!IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG)
				success = false;
		}
	}
	return success;
}

bool LoadBackGround() 
{
	return g_background.LoadIMG("img//background.png", g_screen);
}

void Close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";
	if (!InitData() || !LoadBackGround())
		return -1;

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	bool is_quit = false;

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen);
		game_map.DrawMap(g_screen);

		SDL_RenderPresent(g_screen);
	}
	Close();
	return 0;
}

