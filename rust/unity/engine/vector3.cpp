#include "vector3.hpp"

Vector3::Vector3()
	: x( 0.f )
	, y( 0.f )
	, z( 0.f )
{ }

Vector3::Vector3( float vector_x, float vector_y, float vector_z )
	: x( vector_x )
	, y( vector_y )
	, z( vector_z )
{ }

Vector3::Vector3( const Vector3& vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
	, z( vector[ 2 ] )
{ }

float Vector3::Dot( const Vector3& vector ) const
{
	return ( x * vector[ 0 ] +
					 y * vector[ 1 ] +
					 z * vector[ 2 ] );
}

float Vector3::Length2DSquared() const
{
	return ( x * x +
					 z * z );
}

float Vector3::Length2D() const
{
	return win32::sqrt( x * x +
											z * z );
}

float Vector3::LengthSquared() const
{
	return ( x * x +
					 y * y +
					 z * z );
}

float Vector3::Length() const
{
	return win32::sqrt( x * x +
											y * y +
											z * z );
}

float Vector3::DistanceSquared( const Vector3& vector ) const
{
	const auto direction( *this - vector );
	return direction.LengthSquared();
}

float Vector3::Distance( const Vector3& vector ) const
{
	const auto direction( *this - vector );
	return direction.Length();
}

float Vector3::Normalize()
{
	constexpr auto epsilon = std::numeric_limits< float >::epsilon();

	const auto length = Length();
	const auto factor = ( 1.f / ( length + epsilon ) );

	x *= factor;
	y *= factor;
	z *= factor;

	return length;
}

Vector3 Vector3::Normalized()
{
	auto vector( *this );
	vector.Normalize();
	return std::move( vector );
}

Vector3 Vector3::ToEulerAngles()
{
	const auto length2d = Length2D();

	auto pitch = 0.f;
	auto yaw = 0.f;

	if( length2d > 0.f )
	{
		const auto pitch_radians = win32::atan2( -y, length2d );
		pitch = RadiansToDegrees( pitch_radians );

		const auto yaw_radians = win32::atan2( z, x );
		yaw = RadiansToDegrees( yaw_radians );
	}
	else
	{
		pitch = ( y > 0.f ) ? 270.f : 90.f;
	}

	return { AngleNormalize( pitch ),
					 AngleNormalize( yaw ),
					 0.f };
}

float Vector3::operator[]( std::size_t index ) const
{
	return ( &x )[ index ];
}

float& Vector3::operator[]( std::size_t index )
{
	return ( &x )[ index ];
}

Vector3& Vector3::operator=( const Vector3& vector )
{
	if( std::addressof( vector ) != this )
	{
		x = vector[ 0 ];
		y = vector[ 1 ];
		z = vector[ 2 ];
	}
	return ( *this );
}

Vector3& Vector3::operator+=( float value )
{
	x += value;
	y += value;
	z += value;
	return ( *this );
}

Vector3& Vector3::operator-=( float value )
{
	x -= value;
	y -= value;
	z -= value;
	return ( *this );
}

Vector3& Vector3::operator*=( float value )
{
	x *= value;
	y *= value;
	z *= value;
	return ( *this );
}

Vector3& Vector3::operator/=( float value )
{
	x /= value;
	y /= value;
	z /= value;
	return ( *this );
}

Vector3& Vector3::operator+=( const Vector3& vector )
{
	x += vector[ 0 ];
	y += vector[ 1 ];
	z += vector[ 2 ];
	return ( *this );
}

Vector3& Vector3::operator-=( const Vector3& vector )
{
	x -= vector[ 0 ];
	y -= vector[ 1 ];
	z -= vector[ 2 ];
	return ( *this );
}

Vector3& Vector3::operator*=( const Vector3& vector )
{
	x *= vector[ 0 ];
	y *= vector[ 1 ];
	z *= vector[ 2 ];
	return ( *this );
}

Vector3& Vector3::operator/=( const Vector3& vector )
{
	x /= vector[ 0 ];
	y /= vector[ 1 ];
	z /= vector[ 2 ];
	return ( *this );
}

Vector3 Vector3::operator+( float value ) const
{
	return { x + value,
					 y + value,
					 z + value };
}

Vector3 Vector3::operator-( float value ) const
{
	return { x - value,
					 y - value,
					 z - value };
}

Vector3 Vector3::operator*( float value ) const
{
	return { x * value,
					 y * value,
					 z * value };
}

Vector3 Vector3::operator/( float value ) const
{
	return { x / value,
					 y / value,
					 z / value };
}

Vector3 Vector3::operator+( const Vector3& vector ) const
{
	return { x + vector[ 0 ],
					 y + vector[ 1 ],
					 z + vector[ 2 ] };
}

Vector3 Vector3::operator-( const Vector3& vector ) const
{
	return { x - vector[ 0 ],
					 y - vector[ 1 ],
					 z - vector[ 2 ] };
}

Vector3 Vector3::operator*( const Vector3& vector ) const
{
	return { x * vector[ 0 ],
					 y * vector[ 1 ],
					 z * vector[ 2 ] };
}

Vector3 Vector3::operator/( const Vector3& vector ) const
{
	return { x / vector[ 0 ],
					 y / vector[ 1 ],
					 z / vector[ 2 ] };
}