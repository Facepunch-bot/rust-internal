#include "unity_engine.hpp"

namespace UnityEngine
{

// 
// [ Vector3 ] implementation
// 
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
	return ( x * vector[ 0 ] + y * vector[ 1 ] + z * vector[ 2 ] );
}

float Vector3::Length() const
{
	return win32::sqrt( x * x + y * y + z * z );
}

float Vector3::Length2D() const
{
	return win32::sqrt( x * x + z * z );
}

float Vector3::Distance( const Vector3& vector ) const
{
	const auto direction = ( *this - vector );
	return direction.Length();
}

float Vector3::Distance2D( const Vector3& vector ) const
{
	const auto direction = ( *this - vector );
	return direction.Length2D();
}

float Vector3::Normalize()
{
	const auto length = Length();

	if( length > 0.f )
	{
		x /= length;
		y /= length;
		z /= length;
	}
	else
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	return length;
}

bool Vector3::IsZero() const
{
	return ( x == 0.f &&
					 y == 0.f &&
					 z == 0.f );
}

Vector3 Vector3::ToVector() const
{
	const auto pitch = ToRadians( x );
	const auto yaw = ToRadians( y );

	const auto cp = win32::cos( pitch );
	const auto cy = win32::cos( yaw );

	const auto sp = win32::sin( pitch );
	const auto sy = win32::sin( yaw );

	return { cp * sy, -sp, cp * cy };
}

Vector3 Vector3::ToEulerAngles() const
{
	const auto length = Length();

	const auto pitch = -ToDegrees( win32::asin( y / length ) );
	const auto yaw = ToDegrees( win32::atan2( x, z ) );

	return { pitch, yaw, 0.f };
}

float Vector3::operator[]( std::size_t index ) const
{
	return ( &x )[ index ];
}

float& Vector3::operator[]( std::size_t index )
{
	return ( &x )[ index ];
}

Vector3 Vector3::operator-() const
{
	return { -x, -y, -z };
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

Vector3 Vector3::Zero( 0.f, 0.f, 0.f );
Vector3 Vector3::Forward(0.f, 0.f, 1.f);
Vector3 Vector3::Back(0.f, 0.f, -1.f);

// 
// [ Component ] implementation
// 
Vector3 Component::get_position()
{
	const auto transform = get_transform();

	if( memory::IsAddressValid( transform ) )
	{
		return transform->get_position();
	}

	return Vector3::Zero;
}

// 
// [ Camera ] implementation
// 
bool Camera::WorldToScreen( const Vector3& position, Vector3& output )
{
	const auto& io = ImGui::GetIO();

	if( !memory::IsAddressValid( view ) )
	{
		return false;
	}

	const auto matrix = view->viewMatrix;
	const auto translation = matrix.GetColumn( 3 );

	const auto w = translation.Dot( position ) + matrix[ 3 ][ 3 ];

	if( w < 0.098f )
	{
		return false;
	}

	const auto right = matrix.GetColumn( 0 );
	const auto up = matrix.GetColumn( 1 );

	const auto x = right.Dot( position ) + matrix[ 3 ][ 0 ];
	const auto y = up.Dot( position ) + matrix[ 3 ][ 1 ];

	output[ 0 ] = ( io.DisplaySize[ 0 ] * 0.5f ) * ( 1.f + ( x / w ) );
	output[ 1 ] = ( io.DisplaySize[ 1 ] * 0.5f ) * ( 1.f - ( y / w ) );

	return true;
}

float ToRadians( float degrees )
{
	return ( degrees * ( PiRadians / PiDegrees ) );
}

float ToDegrees( float radians )
{
	return ( radians * ( PiDegrees / PiRadians ) );
}

float AngleNormalize( float angle )
{
	angle = win32::fmod( angle, 360.f );
	if( angle < -180.f )
	{
		angle += 360.f;
	}
	else if( angle > 180.f )
	{
		angle -= 360.f;
	}
	return angle;
}

void AnglesNormalize( Vector3& angles )
{
	angles[ 0 ] = AngleNormalize( angles[ 0 ] );
	angles[ 1 ] = AngleNormalize( angles[ 1 ] );
	angles[ 2 ] = AngleNormalize( angles[ 2 ] );
}

bool WorldToScreen( const Vector3& position, Vector3& output )
{
	auto camera = Camera::get_current();

	if( !memory::IsAddressValid( camera ) )
	{
		return false;
	}

	return camera->WorldToScreen( position, output );
}

bool Physics::Raycast(Vector3 origin, Vector3 direction)
{
	static uintptr_t procedure = 0;

	if (!memory::IsAddressValid(procedure))
	{
		procedure = win32::GetImage(HASH("GameAssembly.dll")) + 0x01AD8750;
	}
	
	if (!memory::IsAddressValid(procedure))
		return false;

	return memory::SecureCall<bool>(procedure, std::cref(origin), std::cref(direction));
}

} // namespace UnityEngine