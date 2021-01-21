#pragma once
#ifndef MAIN_CHARACTER_H_
#define MAIN_CHARACTER_H_
#include "CommonFunc.h"
#include "BaseObject.h"
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
private:
	float x_val_, y_val_;
	float x_pos_, y_pos_;
	float frame_width_, frame_height_;

	SDL_Rect frame_clip_[8];
	Action action_input_;
	int frame_index_;
	int action_status_;
};


#endif