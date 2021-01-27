#pragma once
#ifndef MAIN_CHARACTER_H_
#define MAIN_CHARACTER_H_
#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8;

class MainCharacter : public BaseObject
{
public:
	MainCharacter();
	~MainCharacter();
	enum Direction
	{
		GO_RIGHT,
		GO_LEFT
	};
	bool LoadIMG(std::string path, SDL_Renderer* screen);
	void set_clips();
	void Show(SDL_Renderer* des);
	void HandleActionInput(SDL_Event events, SDL_Renderer* screen);
	void PlayerAction(Map& map_data);
	void CheckColision(Map& map_data);
	void SetMapXY(const int map_x_, const int map_y_) { map_x = map_x_, map_y = map_y_; };
	void CenterEntityToMap(Map& map_data);
private:
	float x_val_, y_val_;
	float x_pos_, y_pos_;
	float frame_width_, frame_height_;

	SDL_Rect frame_clip_[8];
	Action action_input_;
	int frame_index_;
	int action_status_;
	bool on_ground = false;
	int map_x, map_y;
	int comeback_time_;
};


#endif