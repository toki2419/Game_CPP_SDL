#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
}

BulletObject::~BulletObject()
{
}

void BulletObject::HandleMove(const int & x_border, const int & y_border)
{
	if(direction == RIGHT)
		rect_.x += x_val_;
	else
		rect_.x -= x_val_;
	if (rect_.x > x_border || rect_.x < 0)
		is_move = false;
}
