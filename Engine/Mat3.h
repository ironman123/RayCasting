#pragma once
#include "Vec3.h"

template <typename T>
class Mat3
{
public:
	Vec3<T> operator* (const Vec3<T>& v)const
	{
		Vec3<T> out;
		out.x = cells[0][0] * v.x + cells[0][1] * v.y + cells[0][2] * v.w;
		out.y = cells[1][0] * v.x + cells[1][1] * v.y + cells[1][2] * v.w;
		out.w = cells[2][0] * v.x + cells[2][1] * v.y + cells[2][2] * v.w;
		return out;
	}
	Mat3 operator* (const Mat3& rhs)const
	{
		Mat3 out;

		for (int i = 0; i < 3; i++)
		{
			out.cells[0][i] = cells[0][0] * rhs.cells[0][i] + cells[0][1] * rhs.cells[1][i] + cells[0][2] * rhs.cells[2][i];
			out.cells[1][i] = cells[1][0] * rhs.cells[0][i] + cells[1][1] * rhs.cells[1][i] + cells[1][2] * rhs.cells[2][i];
			out.cells[2][i] = cells[2][0] * rhs.cells[0][i] + cells[2][1] * rhs.cells[1][i] + cells[2][2] * rhs.cells[2][i];
		}
		return out;
	}
	Mat3& operator*=(const Mat3& rhs)const
	{
		return *this = *this * rhs;
	}
	static Mat3 Scale(T factor)
	{
		return
		{
			factor, (T)0, (T)0,
			(T)0 ,factor ,(T)0,
			(T)0 , (T)0 ,(T)1
		};
	}
	static Mat3 Identity()
	{
		return
		{ Scale((T)1);
			//(T)1, (T)0, (T)0,
			//(T)0, (T)1, (T)0,
			//(T)0, (T)0, (T)1
		};
	}
	static Mat3 FlipY()
	{
		return
		{
			(T)1, (T)0, (T)0,
			(T)0, -(T)1, (T)0,
			(T)0, (T)0, (T)1
		};
	}
	static Mat3 Rotate(T theta)
	{
		const auto cos = std::cos(theta);
		const auto sin = std::sin(theta);

		return
		{
			cos , -sin , (T)0,
			sin , cos  , (T)0,
			(T)0, (T)0 , (T)1
		};
	}

public:
	T cells[3][3];
};

typedef Mat3<float> Maf3;
using Mad3 = Mat3<double>;
typedef Mat3<int> Mai3;