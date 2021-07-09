#pragma once

#include "math.hpp"

class Vector2
{
public:
	Vector2();
	Vector2( float vector_x, float vector_y );
	Vector2( const Vector2& vector );
	
public:
	float Dot( const Vector2& vector ) const;
	
	float LengthSquared() const;
	float Length() const;

	float DistanceSquared( const Vector2& vector ) const;
	float Distance( const Vector2& vector ) const;

	float Normalize();

public:
	Vector2 Normalized();

public:
	float operator[]( std::size_t index ) const;
	float& operator[]( std::size_t index );

public:
	Vector2& operator=( const Vector2& vector );
	
public:
	Vector2& operator+=( float value );
	Vector2& operator-=( float value );
	Vector2& operator*=( float value );
	Vector2& operator/=( float value );

	Vector2& operator+=( const Vector2& vector );
	Vector2& operator-=( const Vector2& vector );
	Vector2& operator*=( const Vector2& vector );
	Vector2& operator/=( const Vector2& vector );

public:
	Vector2 operator+( float value ) const;
	Vector2 operator-( float value ) const;
	Vector2 operator*( float value ) const;
	Vector2 operator/( float value ) const;

	Vector2 operator+( const Vector2& vector ) const;
	Vector2 operator-( const Vector2& vector ) const;
	Vector2 operator*( const Vector2& vector ) const;
	Vector2 operator/( const Vector2& vector ) const;

public:
	float x = 0.f;	// 0x0000
	float y = 0.f;	// 0x0004
};
// sizeof( Vector2 ) = 0x0008