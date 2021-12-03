#pragma once
#include <vector>
#include "Ball.h"
#include <random>

class Spwaner
{
public:
	Spwaner(std::vector<Ball>& balls, float radius, const Vef2& pos, float vy, float minVX, float maxVX,float spwanPeriod)
		:
		rDist(12.0f,1.5f * radius),
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
			radius = rDist(rng);
			time -= spwanPeriod;
			balls.emplace_back(pos, radius, Vef2{ vXDist(rng),vy });
		}
	}
	void BallPairSpwaner(float dt)
	{
		time += dt;
		if (time > spwanPeriod)
		{
			time -= spwanPeriod;

			radius = rDist(rng);

			//vertical
			balls.emplace_back(Vef2{ 0.0f,-180.0f }, radius, Vef2{ 0.0f,60.0f });
			balls.emplace_back(Vef2{ 0.0f,180.0f }, radius, Vef2{ 0.0f,-60.0f });
			//horizontal
			balls.emplace_back(Vef2{ -180.0f,0.0f }, radius, Vef2{ 50.0f,0.0f });
			balls.emplace_back(Vef2{ 180.0f,0.0f }, radius, Vef2{ -50.0f,0.0f });
			//Diagonal Spwan 
			balls.emplace_back(Vef2{ -180.0f,-180.0f }, radius, Vef2{ 150.0f,50.0f });
			balls.emplace_back(Vef2{ 180.0f,180.0f }, radius,  Vef2{ -150.0f,-50.0f });  
			////L shape Spwan
			//balls.emplace_back(Vef2{ 0.0f,180.0f }, radius, Vef2{ 0.0f,-150.0f });
			//balls.emplace_back(Vef2{ -180.0f,0.0f }, radius, Vef2{ 150.0f,0.0f });
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
	std::uniform_real_distribution<float> rDist;
	std::vector<Ball>& balls;
};