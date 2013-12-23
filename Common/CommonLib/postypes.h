#pragma once

#include <glm/glm.hpp>

#include <cmath>

/// Angle ///

/// <summary>Represents an angle in 2D space.</summary>
template<class T> struct Angle final {
	T Radians;

	T GetDegrees() { return (T) (180.0f / M_PI * Radians); }
	T GetSin() { return sin(Radians); }
	T GetCos() { return cos(Radians); }

	Angle() :
		Radians(0)
	{}
	Angle(T r) :
		Radians(r)
	{}

	Angle<T>& operator=(T r) {
		return Angle<T>(r);
	}
};

// Common variations of Angle
typedef Angle<float> Anglef;