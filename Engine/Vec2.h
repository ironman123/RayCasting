#pragma once
#include <cmath>

template <typename T>
class Vec2
{
public:
	Vec2()
	{}

	Vec2(T in_x, T in_y)
		:
		x(in_x),
		y(in_y)
	{
	}

	Vec2(const Vec2& vect)
		:
		Vec2(vect.x, vect.y)
	{
	}

	template <typename T2>
	explicit operator Vec2<T2>() const
	{
		return { (T2)x, (T2)y };
	}

	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}

	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}

	Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}

	Vec2 operator*(T scaler) const
	{
		return Vec2(x * scaler, y * scaler);
	}

	Vec2& operator*=(T scaler)
	{
		return *this = *this * scaler;
	}

	Vec2 operator/(T scaler) const
	{
		return Vec2(x / scaler, y / scaler);
	}

	Vec2& operator/=(T scaler)
	{
		return *this = *this / scaler;
	}

	bool operator==(const Vec2& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}

	bool operator!=(const Vec2& rhs)const
	{
		return !(*this == rhs);
	}

	T LengthSq() const
	{
		return sq(*this);
	}

	T Length() const
	{
		return sqrt(LengthSq());
	}

	Vec2& Normalize()
	{
		const T length = Length();

		x /= length;
		y /= length;

		return *this;
	}

	Vec2 GetNormalized() const
	{
		Vec2 norm = *this;
		norm.Normalize();
		return norm;
	}

	Vec2 operator-()const
	{
		return Vec2(-x, -y);
	}

	Vec2& operator=(const Vec2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
public:
	T x;
	T y;
};

typedef Vec2<double> Ved2;
typedef Vec2<float> Vef2;
typedef Vec2<int> Vei2;