#include "math.hpp"

#include "../core/map_data.hpp"

#include <xmmintrin.h>

#include <cassert>

#define GET_FLOAT_WORD( i, d )			\
	do																\
	{																	\
		ieee_float_shape_type gf_u;			\
		gf_u.value = ( d );							\
		( i ) = gf_u.word;							\
	}																	\
	while( 0 )

#define SET_FLOAT_WORD( d, i )			\
	do																\
	{																	\
		ieee_float_shape_type sf_u;			\
		sf_u.word = ( i );							\
		( d ) = sf_u.value;							\
	}																	\
	while( 0 )

namespace horizon::win32
{

// 
// constants
// 

constexpr float XM_PI = 3.141592654f;
constexpr float XM_2PI = 6.283185307f;
constexpr float XM_1DIVPI = 0.318309886f;
constexpr float XM_1DIV2PI = 0.159154943f;
constexpr float XM_PIDIV2 = 1.570796327f;
constexpr float XM_PIDIV4 = 0.785398163f;

// 
// imports
// 

double pow( double x, double y )
{
	return g_map_data.pow( x, y );
}

float powf( float x, float y )
{
	return static_cast< float >( pow( static_cast< double >( x ), static_cast< double >( y ) ) );
}

double fmod( double x, double y )
{
	return g_map_data.fmod( x, y );
}

float fmodf( float x, float y )
{
	return static_cast< float >( fmod( static_cast< double >( x ), static_cast< double >( y ) ) );
}

double atof( const char* const data )
{
	return g_map_data.atof( data );
}

double floor( double x )
{
	return g_map_data.floor( x );
}

float floorf( float x )
{
	return static_cast< float >( floor( static_cast< double >( x ) ) );
}

double ceil( double x )
{
	return g_map_data.ceil( x );
}

float ceilf( float x )
{
	return static_cast< float >( ceil( static_cast< double >( x ) ) );
}

void qsort( void* a1, size_t a2, size_t a3, _CoreCrtNonSecureSearchSortCompareFunction a4 )
{
	return g_map_data.qsort( a1, a2, a3, a4 );
}

double atan2( double y, double x )
{
	return g_map_data.atan2( y, x );
}

// 
// implementation
// 

union ieee_float_shape_type
{
	float value;
	std::uint32_t word;
};

float roundf( float x )
{
	std::uint32_t w;
	GET_FLOAT_WORD( w, x );

	const auto exponent_less_127 = static_cast< std::int32_t >( ( w & 0x7f800000 ) >> 23 ) - 127;

	if( exponent_less_127 < 23 )
	{
		if( exponent_less_127 < 0 )
		{
			w &= 0x80000000;

			if( exponent_less_127 == -1 )
			{
				w |= ( static_cast< std::uint32_t >( 127 ) << 23 );
			}
		}
		else
		{
			const auto exponent_mask = 0x007fffffu >> exponent_less_127;

			if( ( w & exponent_mask ) == 0 )
			{
				return x;
			}

			w += 0x00400000 >> exponent_less_127;
			w &= ~exponent_mask;
		}
	}
	else
	{
		if( exponent_less_127 == 128 )
		{
			return x + x;
		}
		else
		{
			return x;
		}
	}

	SET_FLOAT_WORD( x, w );
	return x;
}

float fabsf( float x )
{
	return ( x < 0.f ? -x : x );
}

float sqrtf( float x )
{
	auto root = _mm_set_ss( x );
	root = _mm_sqrt_ss( root );
	return _mm_cvtss_f32( root );
}

float sinf( float x )
{
	auto quotient = XM_1DIV2PI * x;

	if( x >= 0.f )
	{
		quotient = static_cast< float >( static_cast< int >( quotient + 0.5f ) );
	}
	else
	{
		quotient = static_cast< float >( static_cast< int >( quotient - 0.5f ) );
	}

	auto y = x - XM_2PI * quotient;
	auto sign = 0.f;

	if( y > XM_PIDIV2 )
	{
		y = XM_PI - y;
		sign = -1.f;
	}
	else if( y < -XM_PIDIV2 )
	{
		y = -XM_PI - y;
		sign = -1.f;
	}
	else
	{
		sign = +1.f;
	}

	auto y2 = y * y;
	return ( ( ( ( ( ( -2.3889859e-08f * y2 + 2.7525562e-06f ) * y2 - 0.00019840874f ) * y2 + 0.0083333310f ) * y2 - 0.16666667f ) * y2 + 1.f ) * y );
}

float cosf( float x )
{
	auto quotient = XM_1DIV2PI * x;

	if( x >= 0.f )
	{
		quotient = static_cast< float >( static_cast< int >( quotient + 0.5f ) );
	}
	else
	{
		quotient = static_cast< float >( static_cast< int >( quotient - 0.5f ) );
	}

	auto y = x - XM_2PI * quotient;
	auto sign = 0.f;

	if( y > XM_PIDIV2 )
	{
		y = XM_PI - y;
		sign = -1.f;
	}
	else if( y < -XM_PIDIV2 )
	{
		y = -XM_PI - y;
		sign = -1.f;
	}
	else
	{
		sign = +1.f;
	}

	auto y2 = y * y;
	auto p = ( ( ( ( ( -2.6051615e-07f * y2 + 2.4760495e-05f ) * y2 - 0.0013888378f ) * y2 + 0.041666638f ) * y2 - 0.5f ) * y2 + 1.f );

	return ( sign * p );
}

float tanf( float x )
{
	auto s = sinf( x );
	auto c = cosf( x );

	return ( s / c );
}

float asinf( float x )
{
	auto non_negative = ( x >= 0.f );

	auto pox = fabsf( x );
	auto omx = 1.f - pox;

	if( omx < 0.f )
	{
		omx = 0.f;
	}

	auto root = sqrtf( omx );
	auto result = ( ( ( ( ( ( ( -0.0012624911f * pox + 0.0066700901f ) * pox - 0.0170881256f ) * pox + 0.0308918810f ) * pox - 0.0501743046f ) * pox + 0.0889789874f ) * pox - 0.2145988016f ) * pox + 1.5707963050f );

	result *= root;
	return ( non_negative ? ( XM_PIDIV2 - result ) : ( result - XM_PIDIV2 ) );
}

float acosf( float x )
{
	auto non_negative = ( x >= 0.f );

	auto pox = fabsf( x );
	auto omx = 1.f - pox;

	if( omx < 0.f )
	{
		omx = 0.f;
	}

	auto root = sqrtf( omx );
	auto result = ( ( ( ( ( ( ( -0.0012624911f * pox + 0.0066700901f ) * pox - 0.0170881256f ) * pox + 0.0308918810f ) * pox - 0.0501743046f ) * pox + 0.0889789874f ) * pox - 0.2145988016f ) * pox + 1.5707963050f );

	result *= root;
	return ( non_negative ? result : ( XM_PI - result ) );
}

float atanf( float x )
{
	auto x2 = x * x;
	auto root = sqrtf( 1.f + x2 );
	return asinf( x / root );
}

float atan2f( float y, float x )
{
	return static_cast< float >( atan2( static_cast< double >( y ), static_cast< double >( x ) ) );
}

long atol( const char* const data )
{
	return g_map_data.atol( data );
}

int atoi( const char* const data )
{
	return static_cast< int >( atol( data ) );
}

} // namespace horizon::win32