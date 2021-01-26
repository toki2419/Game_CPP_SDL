#include "ImpTimer.h"
#include "CommonFunc.h"

ImpTimer::ImpTimer()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	is_started_ = false;
	is_paused_ = false;
}

ImpTimer::~ImpTimer()
{
}

void ImpTimer::Start()
{
	is_started_ = true;
	is_paused_ - false;
	start_tick_ = SDL_GetTicks();
}

void ImpTimer::Stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void ImpTimer::Pause()
{
	if (is_started_ && !is_paused_)
	{
		is_paused_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_;
	}
}

void ImpTimer::Resume()
{
	if (is_paused_)
	{
		is_paused_ = true;
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}

int ImpTimer::get_ticks()
{
	if (start_tick_)
	{
		if (is_paused_)
			return pause_tick_;
		else
			return SDL_GetTicks() - start_tick_;
	}
	return 0;
}
