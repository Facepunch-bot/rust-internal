#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::win32
{

// 
// imported
// 

double pow( double x, double y );
float powf( float x, float y );
double fmod( double x, double y );
float fmodf( float x, float y );
double atof( const char* const data );

double floor( double x );
float floorf( float x );
double ceil( double x );
float ceilf( float x );

void qsort( void* a1, size_t a2, size_t a3, _CoreCrtNonSecureSearchSortCompareFunction a4 );

double atan2( double y, double x );

// 
// implemented
// 

float roundf( float x );

float fabsf( float x );
float sqrtf( float x );

float sinf( float x );
float cosf( float x );
float tanf( float x );

float asinf( float x );
float acosf( float x );
float atanf( float x );

float atan2f( float y, float x );

float tanf( float x );
float sinf( float x );
float cosf( float x );
float acosf( float x );
float atan2f( float y, float x );
double atof( const char* str );
float floorf( float x );
float ceilf( float x );

// 
// wrappers
// 

inline float pow( float x, float y )
{
	return powf( x, y );
}

inline float fmod( float x, float y )
{
	return fmodf( x, y );
}

inline float mod( float x, float y )
{
	return fmodf( x, y );
}

inline float floor( float x )
{
	return floorf( x );
}

inline float ceil( float x )
{
	return ceilf( x );
}

inline float round( float x )
{
	return roundf( x );
}

inline float fabs( float x )
{
	return fabsf( x );
}

inline float abs( float x )
{
	return fabsf( x );
}

inline float sqrt( float x )
{
	return sqrtf( x );
}

inline float sin( float x )
{
	return sinf( x );
}

inline float cos( float x )
{
	return cosf( x );
}

inline float tan( float x )
{
	return tanf( x );
}

inline float asin( float x )
{
	return asinf( x );
}

inline float acos( float x )
{
	return acosf( x );
}

inline float atan( float x )
{
	return atanf( x );
}

inline float atan2( float y, float x )
{
	return atan2f( y, x );
}

int atoi( const char* const data );
long atol( const char* const data );

} // namespace horizon::win32