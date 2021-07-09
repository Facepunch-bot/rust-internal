#pragma once

#include "math.hpp"

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4( const Matrix4x4& matrix );

public:
	void Transpose();

public:
	Matrix4x4 Transposed();

	Vector3 GetRow( std::size_t index ) const;
	Vector3 GetColumn( std::size_t index ) const;

public:
	const float* operator[]( std::size_t index ) const;
	float* operator[]( std::size_t index );

public:
	float m[ 4 ][ 4 ] = {};
};