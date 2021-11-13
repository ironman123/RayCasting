#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float Mark();
	void Start();
	float Stop();
private:
	std::chrono::steady_clock::time_point last;
};