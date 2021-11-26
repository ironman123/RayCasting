#pragma once
#include "Camera.h"
#include "Mouse.h"

class CamMouseCtrl
{
public:
	CamMouseCtrl(Camera& cam, Mouse& mouse)
		:
		cam(cam),
		mouse(mouse)
	{}
	void Update()
	{
		while (!mouse.IsEmpty())
		{
			auto e = mouse.Read();
			
			switch (e.GetType())
			{
			case Mouse::Event::Type::LPress:
				engaged = true;
				last = Vef2(e.GetPos());
				break;
			case Mouse::Event::Type::LRelease:
				engaged = false;
				break;
			case Mouse::Event::Type::WheelUp:
				cam.SetScale(cam.GetScale() * zoomFactor);
				break;
			case Mouse::Event::Type::WheelDown:
				cam.SetScale(cam.GetScale() / zoomFactor);
				break;
			}
		}

		if (engaged)
		{
			const auto curPos = (Vef2)mouse.GetPos();
			auto delta = curPos - last;
			delta.x = -delta.x;
			cam.MoveBy(delta / cam.GetScale());
			last = curPos;
		}
	}
private:
	Vef2 last;
	bool engaged = false;
	Camera& cam;
	Mouse& mouse;
	static constexpr float zoomFactor = 1.05f;
};
