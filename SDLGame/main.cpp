// SDLGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainCharacter.h"
#include "ImpTimer.h"

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

	ImpTimer fps_time;
	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	MainCharacter main_p;
	main_p.LoadIMG("img/player_right.png", g_screen);
	main_p.set_clips();

	bool is_quit = false;

	while (!is_quit)
	{
		fps_time.Start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			main_p.HandleActionInput(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen);

		Map map_data = game_map.getMap();

		main_p.SetMapXY(map_data.start_x_, map_data.start_y_);
		main_p.PlayerAction(map_data);
		main_p.Show(g_screen);
		main_p.HandleBullet(g_screen);

		game_map.setMap(map_data);
		game_map.DrawMap(g_screen);
		

		SDL_RenderPresent(g_screen);

		int real_time = fps_time.get_ticks();
		int time_one_frame = 1000 / FPS; //1000ms = 1s
		if (real_time < time_one_frame)
			SDL_Delay(time_one_frame - real_time);
	}
	Close();
	return 0;
}

