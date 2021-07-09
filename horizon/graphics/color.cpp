#include "color.hpp"

namespace horizon::graphics
{

Color::Color()
	: m_red( 0.f )
	, m_green( 0.f )
	, m_blue( 0.f )
	, m_alpha( 0.f )
{ }

Color::Color( std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha /*= 255*/ )
	: m_red( ToValue( red ) )
	, m_green( ToValue( green ) )
	, m_blue( ToValue( blue ) )
	, m_alpha( ToValue( alpha ) )
{ }

Color::Color( float red, float green, float blue, float alpha /*= 1.f*/ )
	: m_red( red )
	, m_green( green )
	, m_blue( blue )
	, m_alpha( alpha )
{ }

Color::Color( const Color& color )
	: m_red( color.m_red )
	, m_green( color.m_green )
	, m_blue( color.m_blue )
	, m_alpha( color.m_alpha )
{ }

float* Color::ToArray()
{
	return reinterpret_cast< float* >( this );
}

const float* Color::ToArray() const
{
	return reinterpret_cast< const float* >( this );
}

std::uint32_t Color::ToUInt32() const
{
	return 0;
}

Color& Color::operator=( const Color& color )
{
	m_red = color.m_red;
	m_green = color.m_green;
	m_blue = color.m_blue;
	m_alpha = color.m_alpha;
	return *this;
}

float& Color::operator[]( std::size_t index )
{
	const auto data = ToArray();
	return data[ index ];
}

float Color::operator[]( std::size_t index ) const
{
	const auto data = ToArray();
	return data[ index ];
}

Color Color::Transparent()
{
	return { 0.f, 0.f, 0.f, 0.f };
}

Color Color::Black( float alpha /*= 1.f*/ )
{
	return { 0.f, 0.f, 0.f, alpha };
}

Color Color::White( float alpha /*= 1.f*/ )
{
	return { 1.f, 1.f, 1.f, alpha };
}

Color Color::Red( float alpha /*= 1.f*/ )
{
	return { 1.f, 0.f, 0.f, alpha };
}

Color Color::Green( float alpha /*= 1.f*/ )
{
	return { 0.f, 1.f, 0.f, alpha };
}

Color Color::Blue( float alpha /*= 1.f*/ )
{
	return { 0.f, 0.f, 1.f, alpha };
}

Color Color::Yellow( float alpha /*= 1.f*/ )
{
	return { 1.f, 1.f, 0.f, alpha };
}

Color Color::Orange( float alpha /*= 1.f*/ )
{
	return { 1.f, 0.5f, 0.f, alpha };
}

Color Color::Cyan( float alpha /*= 1.f*/ )
{
	return { 0.f, 0.5f, 1.f, alpha };
}

} // namespace horizon::graphics