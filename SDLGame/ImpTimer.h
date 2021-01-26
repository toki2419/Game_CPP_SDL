#pragma once
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();

	void Start();
	void Stop();
	void Pause();
	void Resume();

	bool is_started() { return is_started_; };
	bool is_paused() { return is_paused_; };

	int get_ticks();
private:
	int start_tick_, pause_tick_;
	bool is_started_, is_paused_;
};
#endif // !IMP_TIMER_H_

