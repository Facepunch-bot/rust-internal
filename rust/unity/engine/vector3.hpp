#pragma once

#include "math.hpp"

class Vector3
{
public:
	Vector3();
	Vector3( float vector_x, float vector_y, float vector_z );
	Vector3( const Vector3& vector );

public:
	float Dot( const Vector3& vector ) const;

	float Length2DSquared() const;
	float Length2D() const;

	float LengthSquared() const;
	float Length() const;

	float DistanceSquared( const Vector3& vector ) const;
	float Distance( const Vector3& vector ) const;

	float Normalize();

public:
	Vector3 Normalized();
	
	Vector3 ToEulerAngles();

public:
	float operator[]( std::size_t index ) const;
	float& operator[]( std::size_t index );

public:
	Vector3& operator=( const Vector3& vector );

public:
	Vector3& operator+=( float value );
	Vector3& operator-=( float value );
	Vector3& operator*=( float value );
	Vector3& operator/=( float value );

	Vector3& operator+=( const Vector3& vector );
	Vector3& operator-=( const Vector3& vector );
	Vector3& operator*=( const Vector3& vector );
	Vector3& operator/=( const Vector3& vector );

public:
	Vector3 operator+( float value ) const;
	Vector3 operator-( float value ) const;
	Vector3 operator*( float value ) const;
	Vector3 operator/( float value ) const;

	Vector3 operator+( const Vector3& vector ) const;
	Vector3 operator-( const Vector3& vector ) const;
	Vector3 operator*( const Vector3& vector ) const;
	Vector3 operator/( const Vector3& vector ) const;

public:
	float x = 0.f;	// 0x0000
	float y = 0.f;	// 0x0004
	float z = 0.f;	// 0x0008
};
// sizeof( Vector3 ) = 0x000C