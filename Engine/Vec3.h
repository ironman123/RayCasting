#pragma once
#include <cmath>
#include "Vec2.h"

template <typename T>
class Vec3
{
public:
	Vec3()
	{}

	Vec3(T in_x, T in_y)
		:
		x(in_x),
		y(in_y)
	{
	}

	Vec3(const Vec3& vect)
		:
		Vec3(vect.x, vect.y)
	{
	}

	explicit Vec3(const Vec2<T>& rhs)
		:
		Vec3(rhs.x, rhs.y)
	{
	}

	explicit operator Vec2<T>()const
	{
		return { x,y };
	}

	template <typename T2>
	explicit operator Vec3<T2>() const
	{
		return { (T2)x, (T2)y };
	}

	Vec3 operator+(const Vec3& rhs) const
	{
		return Vec3(x + rhs.x, y + rhs.y);
	}

	Vec3& operator+=(const Vec3& rhs)
	{
		return *this = *this + rhs;
	}

	Vec3 operator-(const Vec3& rhs) const
	{
		return Vec3(x - rhs.x, y - rhs.y);
	}

	Vec3& operator-=(const Vec3& rhs)
	{
		return *this = *this - rhs;
	}

	Vec3 operator*(T scaler) const
	{
		return Vec3(x * scaler, y * scaler);
	}

	Vec3& operator*=(T scaler)
	{
		return *this = *this * scaler;
	}

	Vec3 operator/(T scaler) const
	{
		return Vec3(x / scaler, y / scaler);
	}

	Vec3& operator/=(T scaler)
	{
		return *this = *this / scaler;
	}

	T operator*(const Vec3& rhs)const
	{
		return x * rhs.x + y * rhs.y;
	}

	bool operator==(const Vec3& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}

	bool operator!=(const Vec3& rhs)const
	{
		return !(*this == rhs);
	}

	T LengthSq() const
	{
		return x * x + y * y;
	}

	T Length() const
	{
		return sqrt(LengthSq());
	}

	Vec3& Normalize()
	{
		const T length = Length();

		x /= length;
		y /= length;

		return *this;
	}

	Vec3 GetNormalized() const
	{
		Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}

	Vec3 operator-()const
	{
		return Vec3(-x, -y);
	}

	Vec3& Rotate(T radians)
	{
		const T sin = std::sin(radians);
		const T cos = std::cos(radians);
		const T new_x = x * cos - y * sin;
		y = x * sin + y * cos;
		x = new_x;
		return *this;
	}

	Vec3 GetRotated(T radians)const
	{
		return Vec3(*this).Rotate(radians);
	}

	Vec3& operator=(const Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		return *this;
	}
public:
	T x;
	T y;
	T w = (T)1; 
};

typedef Vec3<double> Ved3;
typedef Vec3<float> Vef3;
typedef Vec3<int> Vei3;