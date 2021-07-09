#include "vector2.hpp"

Vector2::Vector2()
	: x( 0.f )
	, y( 0.f )
{ }

Vector2::Vector2( float vector_x, float vector_y )
	: x( vector_x )
	, y( vector_y )
{ }

Vector2::Vector2( const Vector2& vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
{ }

float Vector2::Dot( const Vector2& vector ) const
{
	return ( x * vector[ 0 ] +
					 y * vector[ 1 ] );
}

float Vector2::LengthSquared() const
{
	return ( x * x +
					 y * y );
}

float Vector2::Length() const
{
	return win32::sqrt( x * x +
											y * y );
}

float Vector2::DistanceSquared( const Vector2& vector ) const
{
	const auto direction( *this - vector );
	return direction.LengthSquared();
}

float Vector2::Distance( const Vector2& vector ) const
{
	const auto direction( *this - vector );
	return direction.Length();
}

float Vector2::Normalize()
{
	constexpr auto epsilon = std::numeric_limits< float >::epsilon();

	const auto length = Length();
	const auto factor = ( 1.f / ( length + epsilon ) );

	x *= factor;
	y *= factor;

	return length;
}

Vector2 Vector2::Normalized()
{
	auto vector( *this );
	vector.Normalize();
	return std::move( vector );
}

float Vector2::operator[]( std::size_t index ) const
{
	return ( &x )[ index ];
}

float& Vector2::operator[]( std::size_t index )
{
	return ( &x )[ index ];
}

Vector2& Vector2::operator=( const Vector2& vector )
{
	if( std::addressof( vector ) != this )
	{
		x = vector[ 0 ];
		y = vector[ 1 ];
	}
	return ( *this );
}

Vector2& Vector2::operator+=( float value )
{
	x += value;
	y += value;
	return ( *this );
}

Vector2& Vector2::operator-=( float value )
{
	x -= value;
	y -= value;
	return ( *this );
}

Vector2& Vector2::operator*=( float value )
{
	x *= value;
	y *= value;
	return ( *this );
}

Vector2& Vector2::operator/=( float value )
{
	x /= value;
	y /= value;
	return ( *this );
}

Vector2& Vector2::operator+=( const Vector2& vector )
{
	x += vector[ 0 ];
	y += vector[ 1 ];
	return ( *this );
}

Vector2& Vector2::operator-=( const Vector2& vector )
{
	x -= vector[ 0 ];
	y -= vector[ 1 ];
	return ( *this );
}

Vector2& Vector2::operator*=( const Vector2& vector )
{
	x *= vector[ 0 ];
	y *= vector[ 1 ];
	return ( *this );
}

Vector2& Vector2::operator/=( const Vector2& vector )
{
	x /= vector[ 0 ];
	y /= vector[ 1 ];
	return ( *this );
}

Vector2 Vector2::operator+( float value ) const
{
	return { x + value,
					 y + value };
}

Vector2 Vector2::operator-( float value ) const
{
	return { x - value,
					 y - value };
}

Vector2 Vector2::operator*( float value ) const
{
	return { x * value,
					 y * value };
}

Vector2 Vector2::operator/( float value ) const
{
	return { x / value,
					 y / value };
}

Vector2 Vector2::operator+( const Vector2& vector ) const
{
	return { x + vector[ 0 ],
					 y + vector[ 1 ] };
}

Vector2 Vector2::operator-( const Vector2& vector ) const
{
	return { x - vector[ 0 ],
					 y - vector[ 1 ] };
}

Vector2 Vector2::operator*( const Vector2& vector ) const
{
	return { x * vector[ 0 ],
					 y * vector[ 1 ] };
}

Vector2 Vector2::operator/( const Vector2& vector ) const
{
	return { x / vector[ 0 ],
					 y / vector[ 1 ] };
}