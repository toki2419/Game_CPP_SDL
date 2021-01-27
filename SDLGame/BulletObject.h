#pragma once
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"

class BulletObject : public BaseObject
{
public:
	BulletObject();
	~BulletObject();
	enum Bullet_Dir
	{
		RIGHT = 1,
		LEFT = 2
	};
	void Set_X(const int& x) { x_val_ = x; }
	void Set_Y(const int& y) { y_val_ = y; }
	void SetIsMove(const bool& b) { is_move = b; }
	void SetDirectionBullet(const unsigned int& dir) { direction = dir; }

	int Get_X() const { return x_val_; }
	int Get_Y() const { return y_val_; }
	bool GetStatus() const { return is_move; }
	unsigned int GetDirectionBullet() const { return direction; }

	void HandleMove(const int& x_border, const int& y_border);
private:
	int x_val_, y_val_;
	bool is_move;
	unsigned int direction;
};

#endif