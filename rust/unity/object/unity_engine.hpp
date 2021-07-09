#pragma once

#include "../sdk.hpp"

#include "system.hpp"

namespace UnityEngine
{

IL2CPP_NAME_SPACE( "UnityEngine" );

struct Vector3;
struct Bounds;
struct Matrix4x4;

struct Object;
struct Component;
struct Behaviour;
struct MonoBehaviour;
struct Transform;
struct GameObject;
struct Camera;

constexpr auto PiRadians = static_cast< float >( 3.1415926535897932 );
constexpr auto PiDegrees = static_cast< float >( 180.0 );

struct Vector3
{
	Vector3();
	Vector3( float vector_x, float vector_y, float vector_z );
	Vector3( const Vector3& vector );

	float Dot( const Vector3& vector ) const;

	float Length() const;
	float Length2D() const;

	float Distance( const Vector3& vector ) const;
	float Distance2D( const Vector3& vector ) const;

	float Normalize();

	bool IsZero() const;

	Vector3 ToVector() const;
	Vector3 ToEulerAngles() const;

	float operator[]( std::size_t index ) const;
	float& operator[]( std::size_t index );

	Vector3 operator-() const;

	Vector3 operator+( const Vector3& vector ) const;
	Vector3 operator-( const Vector3& vector ) const;
	Vector3 operator*( const Vector3& vector ) const;
	Vector3 operator/( const Vector3& vector ) const;

	static Vector3 Zero;

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	static Vector3 Forward;
	static Vector3 Back;
};
// sizeof( Vector3 ) = 0x000C

struct Bounds
{
	Vector3 m_Center = { };		// 0x0000
	Vector3 m_Extents = { };	// 0x000C
};
// sizeof( Bounds ) = 0x0018

struct Matrix4x4
{
	Matrix4x4()
		: m()
	{ }

	Matrix4x4( const Matrix4x4& matrix )
	{
		for( auto row = 0; row < 4; row++ )
		{
			for( auto column = 0; column < 4; column++ )
			{
				m[ row ][ column ] = matrix.m[ row ][ column ];
			}
		}
	}

	void Transpose()
	{
		for( auto row = 0; row < 4; row++ )
		{
			for( auto column = 0; column < 4; column++ )
			{
				m[ row ][ column ] = m[ column ][ row ];
			}
		}
	}

	Matrix4x4 Transposed() const
	{
		auto matrix( *this );
		matrix.Transpose();
		return std::move( matrix );
	}

	Vector3 GetRow( std::size_t index ) const
	{
		return { m[ index ][ 0 ], m[ index ][ 1 ], m[ index ][ 2 ] };
	}

	Vector3 GetColumn( std::size_t index ) const
	{
		return { m[ 0 ][ index ], m[ 1 ][ index ], m[ 2 ][ index ] };
	}

	Vector3 GetAxis( std::size_t index ) const
	{
		return { m[ index ][ 0 ], m[ index ][ 1 ], m[ index ][ 2 ] };
	}

	const float* operator[]( std::size_t index ) const
	{
		return m[ index ];
	}

	float* operator[]( std::size_t index )
	{
		return m[ index ];
	}

	float m[ 4 ][ 4 ] = { };
};

struct Object : Il2CppObject
{
	bool IsA( const Il2CppClass* object )
	{
		auto super = klass;

		while( memory::IsAddressValid( super ) )
		{
			if( super == object )
			{
				return true;
			}

			super = super->parent;
		}

		return false;
	}

	IL2CPP_CLASS( "Object" );
	IL2CPP_FIELD( std::intptr_t, m_CachedPtr );
	IL2CPP_PROPERTY( System::String*, name );
};

struct Component : Object
{
	Vector3 get_position();

	IL2CPP_CLASS( "Component" );
	IL2CPP_PROPERTY( Transform*, transform );
	IL2CPP_PROPERTY( GameObject*, gameObject );
};

struct Behaviour : Component
{
	IL2CPP_CLASS( "Behaviour" );
};

struct MonoBehaviour : Behaviour
{
	IL2CPP_CLASS( "MonoBehaviour" );
};

struct Transform : Component
{
	IL2CPP_CLASS( "Transform" );
	IL2CPP_PROPERTY( Vector3, position );
	IL2CPP_PROPERTY( Vector3, localPosition );
	IL2CPP_PROPERTY( Vector3, eulerAngles );
	IL2CPP_PROPERTY( Vector3, localEulerAngles );
	IL2CPP_PROPERTY( Vector3, right );
	IL2CPP_PROPERTY( Vector3, up );
	IL2CPP_PROPERTY( Vector3, forward );
	IL2CPP_PROPERTY( Vector3, localScale );
};

struct GameObject : Object
{
	IL2CPP_CLASS( "GameObject" );
	IL2CPP_PROPERTY( Transform*, transform );
	IL2CPP_PROPERTY( std::int32_t, layer );
	IL2CPP_PROPERTY( System::String*, tag );
	IL2CPP_PROPERTY( GameObject*, gameObject );
};

struct Camera : Behaviour
{
	struct View
	{
		FIELD_PAD( 0x00DC );				// 0x0000
		Matrix4x4 viewMatrix = { };	// 0x00DC
	};

	View* view = nullptr;					// 0x0018

	bool WorldToScreen( const Vector3& position, Vector3& output );

	IL2CPP_CLASS( "Camera" );
	IL2CPP_STATIC_PROPERTY( Camera*, main );
	IL2CPP_STATIC_PROPERTY( Camera*, current );
	IL2CPP_PROPERTY(float, fieldOfView);
	IL2CPP_PROPERTY( Matrix4x4, worldToCameraMatrix );
	IL2CPP_PROPERTY( Matrix4x4, projectionMatrix );
};

struct Physics
{
	static bool Raycast(Vector3 origin, Vector3 direction);
};

struct ScriptableObject : Object
{
	IL2CPP_CLASS( "ScriptableObject" );
};

struct Collider : Component
{
	IL2CPP_CLASS( "Collider" );
	IL2CPP_PROPERTY( Bounds, bounds );
};

struct BoxCollider : Collider
{
	IL2CPP_CLASS( "BoxCollider" );
	IL2CPP_PROPERTY( Vector3, center );
	IL2CPP_PROPERTY( Vector3, size );
};

float ToRadians( float degrees );
float ToDegrees( float radians );

float AngleNormalize( float angle );
void AnglesNormalize( Vector3& angles );

bool WorldToScreen( const Vector3& position, Vector3& output );

} // namespace UnityEngine

using UnityEngine::Vector3;
using UnityEngine::Camera;