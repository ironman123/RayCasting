#pragma once
#include "Camera.h"
#include "Mouse.h"

template <typename T>
class CamMouseCtrl
{
public:
	CamMouseCtrl(Camera& cam, Mouse& mouse, const Keyboard& kbd)
		:
		kbd(kbd),
		cam(cam),
		mouse(mouse)
	{}
	void Update(float dt)
	{
		if (kbd.KeyIsPressed('E'))
		{
			cam.SetAngle(cam.GetAngle() + dt);
		}
		else if (kbd.KeyIsPressed('Q'))
		{
			cam.SetAngle(cam.GetAngle() - dt);
		}

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
			delta.Rotate(-cam.GetAngle());
			cam.MoveBy(delta / cam.GetScale());
			last = curPos;
		}
	}
private:
	Mouse& mouse;
	const Keyboard& kbd;
	Vef2 last;
	bool engaged = false;
	Camera& cam;
	
	static constexpr float zoomFactor = 1.05f;
};
