#pragma once
#include "header.h"

//credits https://github.com/A5-/CSGO-External/blob/master/csgo-extern/utils/math.h

#define M_RADPI		57.295779513082f
#define M_PI		3.14159265358979323846
#define M_PI_F		((float)(M_PI))

#define SQUARE( a ) a*a
#define DEG2RAD( x  )  ( (float)(x) * (float)( M_PI_F / 180.f ) )
#define RAD2DEG( x  )  ( (float)(x) * (float)( 180.f/M_PI_F ) )

#pragma warning ( disable : 4244 )

class Matrix3x4
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};

		float m[3][4];
		float mm[12];
	};

	inline vec3& get_axis(int i)
	{
		return *(vec3*)&m[i][0];
	}
};

class Matrix4x4
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};

		float m[4][4];
		float mm[16];
	};

	inline vec3& get_axis(int i)
	{
		return *(vec3*)&m[i][0];
	}
};

void inline sincos(float radians, float* sine, float* cosine)
{
	_asm
	{
		fld		DWORD PTR[radians]
		fsincos

		mov edx, DWORD PTR[cosine]
		mov eax, DWORD PTR[sine]

		fstp DWORD PTR[edx]
		fstp DWORD PTR[eax]
	}

	*sine = sin(radians);
	*cosine = cos(radians);
}

inline void angle_vectors(vec3& angles, vec3* forward)
{

	float sr, sp, sy, cr, cp, cy;

	sincos(DEG2RAD(angles[0]), &sy, &cy);
	sincos(DEG2RAD(angles[1]), &sp, &cp);
	sincos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
}

inline void angle_vectors(const vec3& angles, vec3* forward, vec3* right, vec3* up)
{

	float sr, sp, sy, cr, cp, cy;

	sincos(DEG2RAD(angles[0]), &sy, &cy);
	sincos(DEG2RAD(angles[1]), &sp, &cp);
	sincos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

inline float dot_product(vec3& v1, float* v2)
{
	return v1.x * v2[0] + v1.y * v2[1] + v1.z * v2[2];
}

inline float dot(const vec3& v1, vec3& v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline void vector_transform(vec3& in1, Matrix3x4& in2, vec3& out)
{
	out.x = dot_product(in1, in2.m[0]) + in2.m[0][3];
	out.y = dot_product(in1, in2.m[1]) + in2.m[1][3];
	out.z = dot_product(in1, in2.m[2]) + in2.m[2][3];
}

inline float vector_length(vec3& vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

inline float vector_distance(vec3& fVec1, vec3& fVec2)
{
	return sqrtf(pow(fVec1.x - fVec2.x, 2) + pow(fVec1.y - fVec2.y, 2) + pow(fVec1.z - fVec2.z, 2));
}

inline void make_vector(vec3 angle, vec3& vector)
{
	float pitch = float(angle[0] * M_PI / 180);
	float yaw = float(angle[1] * M_PI / 180);
	float tmp = float(cos(pitch));
	vector[0] = float(-tmp * -cos(yaw));
	vector[1] = float(sin(yaw) * tmp);
	vector[2] = float(-sin(pitch));
}

inline vec3 calc_angle(vec3 PlayerPos, vec3 EnemyPos)
{
	vec3 AimAngles;
	vec3 delta = PlayerPos - EnemyPos;
	float hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y));
	AimAngles.x = atanf(delta.z / hyp) * M_RADPI;
	AimAngles.y = atanf(delta.y / delta.x) * M_RADPI;
	AimAngles.z = 0.0f;
	if (delta.x >= 0.0)
		AimAngles.y += 180.0f;

	return AimAngles;
}

inline float get_fov(vec3 angle, vec3 src, vec3 dst)
{
	vec3 ang, aim;
	ang = calc_angle(src, dst);
	make_vector(angle, aim);
	make_vector(ang, ang);

	float mag = sqrtf(pow(aim.x, 2) + pow(aim.y, 2) + pow(aim.z, 2));
	float u_dot_v = dot(aim, ang);

	return RAD2DEG(acos(u_dot_v / (pow(mag, 2))));
}

inline void vector_angles(const vec3& dir, vec3& angles)
{
	float hyp = sqrtf((dir.x * dir.x) + (dir.y * dir.y));
	angles.x = atanf(dir.z / hyp) * M_RADPI;
	angles.y = atanf(dir.y / dir.x) * M_RADPI;
	angles.z = 0.0f;
	if (dir.x >= 0.0)
		angles.y += 180.0f;
}

inline void clamp_angle(vec3& angles)
{
	if (angles.x < -89.0f)
		angles.x = 89.0f;
	if (angles.x > 89.0f)
		angles.x = 89.0f;
	if (angles.y < -180.0f)
		angles.y += 360.0f;
	if (angles.y > 180.0f)
		angles.y -= 360.0f;
	if (angles.z != 0.0f)
		angles.z = 0.0f;
}

inline void vector_normalize(vec3& v)
{
	float l = vector_length(v);
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
}

inline void smooth_angle(const vec3& ViewAngle, vec3& DestAngles, float smooth)
{
	vec3 vecDelta = ViewAngle - DestAngles;
	clamp_angle(vecDelta);
	DestAngles = ViewAngle - vecDelta / 100.0f * smooth;
}

inline vec3 angle_to_direction(vec3 angle)
{
	// Convert angle to radians 
	angle.x = (float)DEG2RAD(angle.x);
	angle.y = (float)DEG2RAD(angle.y);

	float sinYaw = sin(angle.y);
	float cosYaw = cos(angle.y);

	float sinPitch = sin(angle.x);
	float cosPitch = cos(angle.x);

	vec3 direction;
	direction.x = cosPitch * cosYaw;
	direction.y = cosPitch * sinYaw;
	direction.z = -sinPitch;

	return direction;
}

inline bool WorldToScreen(const vec3& from, vec3& to, Matrix4x4* vm)
{
	if (!vm)
		return false;

	to.x	= vm->m[0][0] * from.x + vm->m[0][1] * from.y + vm->m[0][2] * from.z + vm->m[0][3];
	to.y	= vm->m[1][0] * from.x + vm->m[1][1] * from.y + vm->m[1][2] * from.z + vm->m[1][3];
	float w	= vm->m[3][0] * from.x + vm->m[3][1] * from.y + vm->m[3][2] * from.z + vm->m[3][3];

	if (w < 0.01f)
		return false;

	auto inv = 1.0f / w;
	to.x *= inv;
	to.y *= inv;

	RECT rc;
	if (!GetWindowRect(FindWindow("Valve001", 0), &rc))
		return false;

	auto width = rc.left - rc.right;
	auto height = rc.top - rc.bottom;

	float x = (float)width / 2;
	float y = (float)height / 2;

	x += 0.5f * to.x * (float) rc.right + (rc.right / 2.f);
	y -= 0.5f * to.y * (float) rc.bottom - (rc.bottom / 2.f);

	to.x = x;
	to.y = y;

	return true;
}