#pragma once

#include "foundation/Vector2f.h"

//--------------------------------------------------------------------------------
/**
	Utility class for representing an angle.
*/
class Angle
{
public:
	// Ctor
	Angle() : m_angle(0) {}

	// Ctor - watchout DO NOT USE THIS CTOR!!
	Angle(float value) : m_angle(value) {testBounds();}

	// Increments the angle by the specified value in radians
	void setRadians(float value)
	{

		m_angle = value * 180.0 /__PI;
		testBounds();
	}

	// Increments the angle by the specified value in degrees
	void setDegrees(float value)
	{
		m_angle = value;
		testBounds();
	}

	// Increments the angle by the specified value in radians
	void addRadians(float value)
	{
		m_angle += value * 180.0 /__PI;
		testBounds();
	}

	// Increments the angle by the specified value in degrees
	void addDegrees(float value)
	{
		m_angle += value;
		testBounds();
	}

	// Returns the angle in the [-PI,PI] interval
	float getRadians()
	{
		return m_angle * __PI / 180.0;
	}

	// Returns the angle in the [-180.0,180.0] interval
	float getDegrees()
	{
		return m_angle;
	}

	// Operators
	Angle operator -(const Angle& rhs)
	{
		return Angle(m_angle - rhs.m_angle);
	}
	Angle operator +(const Angle& rhs)
	{
		return Angle(m_angle + rhs.m_angle);
	}

	void testBounds()
	{
		if(m_angle < 0)
			m_angle += 360.0f;
		if(m_angle > 360)
			m_angle -= 360.0f;
	}

	// Utility function for obtaining the angle of a vector
	static Angle getVectorAngle(const Vector2f& v)
	{
		if(v.x < 0.01f && v.x > -0.01f)
			return Angle(0);

		float radAngle = float(atan(v.y / v.x));
		if(v.x < 0.0f)
		{
			radAngle += __PI;
		}
		return Angle(radAngle * 180.0 /__PI);
	}

	// Trigonometric constants
	static const float __PI;
	static const float __TWO_PI;

private:
	float m_angle;
};
