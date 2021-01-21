#include "MainCharacter.h"

MainCharacter::MainCharacter()
{
	x_val_ = 0, y_val_ = 0;
	x_pos_ = 0, y_pos_ = 0;
	frame_width_ = 0, frame_height_ = 0;
	frame_index_ = 0;
	action_status_ = 0;
}

MainCharacter::~MainCharacter()
{
}

bool MainCharacter::LoadIMG(std::string path, SDL_Renderer * screen)
{
	bool res = BaseObject::LoadIMG(path, screen);
	if(res)
	{
		frame_width_ = rect_.w/8;
		frame_height_ = rect_.h;
	}
	return res;
}

void MainCharacter::set_clips()
{
	if (frame_width_ > 0 & frame_height_ > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip_[i].x = i * frame_width_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = frame_width_;
			frame_clip_[i].h = frame_height_;
		}
	}
}

void MainCharacter::Show(SDL_Renderer * des)
{
	if (action_status_ == GO_RIGHT)
		LoadIMG("img/player_right.png", des);
	else
		LoadIMG("img/player_left.png", des);

	if (action_input_.left_ == 1 || action_input_.right_ == 1)
		frame_index_++;
	else
		frame_index_ = 0;

	if (frame_index_ > 7)
		frame_index_ = 0;

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip_[frame_index_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, frame_width_, frame_height_ };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}

void MainCharacter::HandleActionInput(SDL_Event events, SDL_Renderer * screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			action_status_ = GO_LEFT;
			action_input_.left_ = 1;
		}
		break;
		case SDLK_RIGHT:
		{
			action_status_ = GO_RIGHT;
			action_input_.right_ = 1;
		}
		break;
		}
	}

	if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
			action_input_.left_ = 0;
			break;
		case SDLK_RIGHT:
			action_input_.right_ = 0;
			break;
		}
	}
}
