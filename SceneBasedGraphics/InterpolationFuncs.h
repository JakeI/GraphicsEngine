#pragma once


namespace InterpolationFuncs {
	
	template <class T> T step(const T & a, const T & b, float t) {
		if (t < 0.5f) return a;
		else return b;
	}

	template <class T> T linear(const T & a, const T & b, float t) { 
		return a*(1.0f - t) + b*t; 
	}

	template <class T> T cosine(const T & a, const T & b, float t) { 
		float s = (1.0f - cosf(t*(float)M_PI)) / 2.0f;
		return a*(1.0f - s) + b*s;
	}
};

