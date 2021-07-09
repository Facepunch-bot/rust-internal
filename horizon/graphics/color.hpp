#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::graphics
{

class Color
{
protected:
	constexpr float ToValue( std::uint8_t value )
	{
		return ( static_cast< float >( value ) / 255.f );
	}

	constexpr std::uint8_t ToValue( float value )
	{
		return static_cast< std::uint8_t >( value * 255.f );
	}

public:
	Color();
	Color( std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255 );
	Color( float red, float green, float blue, float alpha = 1.f );
	Color( const Color& color );

public:
	float* ToArray();
	const float* ToArray() const;

	std::uint32_t ToUInt32() const;

public:
	Color& operator=( const Color& color );

public:
	float& operator[]( std::size_t index );
	float operator[]( std::size_t index ) const;

public:
	static Color Transparent();
	static Color Black( float alpha = 1.f );
	static Color White( float alpha = 1.f );
	static Color Red( float alpha = 1.f );
	static Color Green( float alpha = 1.f );
	static Color Blue( float alpha = 1.f );
	static Color Yellow( float alpha = 1.f );
	static Color Orange( float alpha = 1.f );
	static Color Cyan( float alpha = 1.f );

public:
	float m_red = 0.f;
	float m_green = 0.f;
	float m_blue = 0.f;
	float m_alpha = 0.f;
};

} // namespace horizon::graphics