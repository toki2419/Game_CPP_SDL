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
	Map getMap() const { return game_map_; };
	void setMap(Map& map_data) { game_map_ = map_data; };
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};

#endif
