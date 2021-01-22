#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_
#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMat : public BaseObject
{
public:
	TileMat() {};
	~TileMat() {};

private:
};

class GameMap
{
public:
	GameMap() {};
	~GameMap() {};
	void LoadMap(std::string fileName);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	const Map getMap() { return game_map_; };
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};

#endif
