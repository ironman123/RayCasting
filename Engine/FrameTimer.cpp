#include "FrameTimer.h"
using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	auto oldLast = last;
	last = steady_clock::now();

	duration<float> dur = (last - oldLast);

	return dur.count();
}

void FrameTimer::Start()
{
	last = steady_clock::now();
}

float FrameTimer::Stop()
{
	auto oldLast = last;
	last = steady_clock::now();
	duration<float, std::milli> dur = last - oldLast;

	return dur.count();
}
