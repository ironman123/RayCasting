#pragma once
#include <cmath>

template <typename T>
class Vec2
{
public:
	Vec2() = default;

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

	T GetLengthSq() const
	{
		return x * x + y * y;
	}

	T Length() const
	{
		return (T)std::sqrt(GetLengthSq());
	}

	Vec2& Normalize()
	{
		return *this = GetNormalized();
	}

	Vec2 GetNormalized() const
	{
		const T len = GetLength();

		if (len != T(0))
		{
			return *this / len;
		}
		return *this;
	}
public:
	T x;
	T y;
};

typedef Vec2<float> Vef2;
typedef Vec2<int> Vei2;