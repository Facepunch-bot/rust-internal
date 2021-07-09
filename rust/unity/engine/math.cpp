#include "math.hpp"
#include "vector3.hpp"

float AngleNormalize( float angle )
{
	angle = win32::fmod( angle, 360.f );

	if( angle > 180.f )
	{
		angle -= 360.f;
	}
	else if( angle < 180.f )
	{
		angle += 360.f;
	}

	return angle;
}

void AnglesNormalize( Vector3& angles )
{
	angles[ 0 ] = AngleNormalize( angles[ 0 ] );
	angles[ 1 ] = AngleNormalize( angles[ 1 ] );
	angles[ 2 ] = AngleNormalize( angles[ 2 ] );
}

void AnglesClamp( Vector3& angles )
{
	angles[ 0 ] = std::clamp( angles[ 0 ], -89.f, 89.f );
	angles[ 1 ] = std::clamp( angles[ 1 ], -180.f, 180.f );
	angles[ 2 ] = 0.f;
}