#include "MainCharacter.h"

MainCharacter::MainCharacter()
{
	x_val_ = 0, y_val_ = 0;
	x_pos_ = 0, y_pos_ = 0;
	frame_width_ = 0, frame_height_ = 0;
	frame_index_ = 0;
	action_status_ = 0;
	action_input_.down_ = action_input_.up_ = action_input_.left_ = action_input_.right_ = action_input_.jump_ = 0;
	map_x = map_y = 0;
	comeback_time_ = 0;
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

void MainCharacter::UpdatePlayerIMG(SDL_Renderer * des)
{
	std::string p_Img = "";
	if (on_ground)
	{
		if (action_status_ == GO_RIGHT)
			p_Img = "img/player_right.png";
		else
			p_Img = "img/player_left.png";
	}
	else
	{
		if (action_status_ == GO_RIGHT)
			p_Img = "img/jum_right.png";
		else
			p_Img = "img/jum_left.png";
	}
	LoadIMG(p_Img, des);
}

void MainCharacter::set_clips()
{
	if (frame_width_ > 0 && frame_height_ > 0)
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
	if (comeback_time_ > 0)
		return;
	UpdatePlayerIMG(des);
	
	if (action_input_.left_ == 1 || action_input_.right_ == 1)
		frame_index_++;
	else
		frame_index_ = 0;

	if (frame_index_ > 7)
		frame_index_ = 0;

	rect_.x = x_pos_ - map_x;
	rect_.y = y_pos_ - map_y;

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
			action_input_.right_ = 0;
		}
		break;
		case SDLK_RIGHT:
		{
			action_status_ = GO_RIGHT;
			action_input_.right_ = 1;
			action_input_.left_ = 0;
		}
		break;
		case SDLK_SPACE:
		{
			action_input_.jump_ = 1;
		}
		break;
		case SDLK_LALT:
		{
			BulletObject* bullet = new BulletObject();
			bullet->LoadIMG("img/bullet_1.png", screen);
			bullet->SetRect(this->rect_.x + frame_width_ - 20, this->rect_.y + frame_height_ * 0.3);
			bullet->Set_X(20);
			bullet->SetIsMove(true);
			if (action_status_ == GO_RIGHT)
			{
				bullet->SetDirectionBullet(bullet->RIGHT);
				bullet->SetRect(this->rect_.x + frame_width_ - 20, this->rect_.y + frame_height_ * 0.25);
			}
			if (action_status_ == GO_LEFT)
			{
				bullet->SetDirectionBullet(bullet->LEFT);
				bullet->SetRect(this->rect_.x, this->rect_.y + frame_height_ * 0.25);
			}
			p_bullet_list_.push_back(bullet);
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

void MainCharacter::HandleBullet(SDL_Renderer * screen)
{
	for (int i = 0; i < p_bullet_list_.size(); i++) 
	{
		BulletObject* bullet = p_bullet_list_[i];
		if (bullet)
		{
			if (bullet->GetStatus())
			{
				bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				bullet->Render(screen);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				delete bullet;
				bullet = NULL;
			}
		}
	}
}

void MainCharacter::PlayerAction(Map & map_data)
{
	if(comeback_time_ > 0)
	{
		comeback_time_--;
		if (comeback_time_ == 0)
		{
			x_val_ = 0;
			y_val_ = 0;
			y_pos_ = 0;
			x_pos_ -= 4 * TILE_SIZE;
			if (x_pos_ < 0)
				x_pos_ = 0;
			on_ground = false;
		}
		return;
	}
	x_val_ = 0;
	y_val_ += GRAVITY_SPEED;

	if (y_val_ > MAX_FALL_SPEED)
		y_val_ = MAX_FALL_SPEED;

	if (action_input_.right_ == 1)
	{
		x_val_ += PLAYER_SPEED;
	}
	if (action_input_.left_ == 1)
	{
		x_val_ -= PLAYER_SPEED;
	}
	if (action_input_.jump_ == 1)
	{
		if (on_ground) {
			y_val_ = -18;
		}
		on_ground = false;
		action_input_.jump_ = 0;
	}
	CheckColision(map_data);
	CenterEntityToMap(map_data);
}

void MainCharacter::CheckColision(Map & map_data)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	//check horizontal
	int height_min = frame_height_ < TILE_SIZE ? frame_height_ : TILE_SIZE;
	
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + frame_width_ - 1) / TILE_SIZE;
	y1 = y_pos_ / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)//move right
		{
			if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= frame_width_ + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0)//move left
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
			{
				x_pos_ = (x1 + 1)*TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//check vetical
	int width_min = frame_width_ < TILE_SIZE ? frame_width_ : TILE_SIZE;

	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;
	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + frame_height_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x2] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= frame_height_ + 1;
				y_val_ = 0;
				on_ground = true;
			}
		}
		else if (y_val_ < 0)
		{
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y1][x1] != BLANK_TILE)
			{
				y_pos_ = ++y1*TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0)
		x_pos_ = 0;
	else if (x_pos_ + frame_width_ > map_data.max_x_)
		x_pos_ = map_data.max_x_ - frame_width_ - 1;
	if (y_pos_ > map_data.max_y_)
		comeback_time_ = 60;
}

void MainCharacter::CenterEntityToMap(Map & map_data)
{
	map_data.start_x_ = x_pos_ - SCREEN_WIDTH / 2;
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - SCREEN_HEIGHT / 2;
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}
