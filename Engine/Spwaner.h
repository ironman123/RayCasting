#pragma once
#include <vector>
#include "Ball.h"
#include <random>

class Spwaner
{
public:
	Spwaner(std::vector<Ball>& balls, float radius, const Vef2& pos, float vy, float minVX, float maxVX,float spwanPeriod)
		:
		radius(radius),
		pos(pos),
		balls(balls),
		spwanPeriod(spwanPeriod),
		vXDist(minVX,maxVX),
		vy(vy)
	{
	}
	void Update(float dt)
	{
		time += dt;
		if (time > spwanPeriod)
		{
			time -= spwanPeriod;
			balls.emplace_back(pos, radius, Vef2{ vXDist(rng),vy });
		}
	}
private:
	float radius;
	float spwanPeriod;
	float time = 0.0f;
	Vef2 pos;
	float vy;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_real_distribution<float> vXDist;
	std::vector<Ball>& balls;
};