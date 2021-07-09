#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>
#include <horizon/memory/secure_call.hpp>
#include <horizon/memory/system_call.hpp>

#include <horizon/win32/basic.hpp>
#include <horizon/win32/image.hpp>
#include <horizon/win32/math.hpp>
#include <horizon/win32/process.hpp>
#include <horizon/win32/string.hpp>
#include <horizon/win32/time.hpp>
#include <horizon/win32/trace.hpp>

using namespace horizon;

constexpr float PiRadians = static_cast< float >( 3.1415926535897932 );
constexpr float PiDegrees = static_cast< float >( 180.0 );

class Vector2;
class Vector3;

class Matrix4x4;

constexpr float DegreesToRadians( float degrees )
{
	return ( degrees * ( PiRadians / PiDegrees ) );
}

constexpr float RadiansToDegrees( float radians )
{
	return ( radians * ( PiDegrees / PiRadians ) );
}

float AngleNormalize( float angle );

void AnglesNormalize( Vector3& angles );
void AnglesClamp( Vector3& angles );