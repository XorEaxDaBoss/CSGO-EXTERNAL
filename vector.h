#pragma once

class vec3
{
public:
	float x, y, z;

	vec3()
	{
		x = y = z = 0.0f;
	}

	vec3(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	vec3(float XYZ)
	{
		x = XYZ; y = XYZ; z = XYZ;
	}

	vec3(float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	vec3(const float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	inline vec3& operator=(const vec3& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	inline vec3& operator=(const float* v)
	{
		x = v[0]; y = v[1]; z = v[2]; return *this;
	}

	inline float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	inline float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	inline vec3& operator+=(const vec3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline vec3& operator-=(const vec3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline vec3& operator*=(const vec3& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	inline vec3& operator/=(const vec3& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	inline vec3& operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	inline vec3& operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	inline vec3& operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	inline vec3& operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	inline vec3 operator-() const
	{
		return vec3(-x, -y, -z);
	}

	inline vec3 operator+(const vec3& v) const
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	inline vec3 operator-(const vec3& v) const
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	inline vec3 operator*(const vec3& v) const
	{
		return vec3(x * v.x, y * v.y, z * v.z);
	}

	inline vec3 operator/(const vec3& v) const
	{
		return vec3(x / v.x, y / v.y, z / v.z);
	}

	inline vec3 operator+(float v) const
	{
		return vec3(x + v, y + v, z + v);
	}

	inline vec3 operator-(float v) const
	{
		return vec3(x - v, y - v, z - v);
	}

	inline vec3 operator*(float v) const
	{
		return vec3(x * v, y * v, z * v);
	}

	inline vec3 operator/(float v) const
	{
		return vec3(x / v, y / v, z / v);
	}

	inline float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	inline float LengthSqr() const
	{
		return (x * x + y * y + z * z);
	}

	inline float LengthXY() const
	{
		return sqrtf(x * x + y * y);
	}

	inline float LengthXZ() const
	{
		return sqrtf(x * x + z * z);
	}

	inline float DistTo(const vec3& v) const
	{
		return (*this - v).Length();
	}

	inline float Dot(const vec3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	inline vec3 Cross(const vec3& v) const
	{
		return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	inline bool IsZero() const
	{
		return (x > -0.01f && x < 0.01f
			&& y > -0.01f && y < 0.01f
			&& z > -0.01f && z < 0.01f);
	}
};