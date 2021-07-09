#include "matrix4x4.hpp"
#include "vector3.hpp"

Matrix4x4::Matrix4x4()
	: m()
{ }

Matrix4x4::Matrix4x4( const Matrix4x4& matrix )
	: m()
{
	for( auto row = 0; row < 4; row++ )
	{
		for( auto column = 0; column < 4; column++ )
		{
			m[ row ][ column ] = matrix[ row ][ column ];
		}
	}
}

void Matrix4x4::Transpose()
{
	for( auto row = 0; row < 4; row++ )
	{
		for( auto column = 0; column < 4; column++ )
		{
			m[ row ][ column ] = m[ column ][ row ];
		}
	}
}

Matrix4x4 Matrix4x4::Transposed()
{
	auto matrix( *this );
	matrix.Transpose();
	return std::move( matrix );
}

Vector3 Matrix4x4::GetRow( std::size_t index ) const
{
	return { m[ index ][ 0 ],
					 m[ index ][ 1 ],
					 m[ index ][ 2 ] };
}

Vector3 Matrix4x4::GetColumn( std::size_t index ) const
{
	return { m[ 0 ][ index ],
					 m[ 1 ][ index ],
					 m[ 2 ][ index ] };
}

const float* Matrix4x4::operator[]( std::size_t index ) const
{
	return m[ index ];
}

float* Matrix4x4::operator[]( std::size_t index )
{
	return m[ index ];
}