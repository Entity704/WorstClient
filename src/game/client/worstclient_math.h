/* (c) WorstClient. See licence.txt in the root of the distribution for more information. */
#ifndef GAME_CLIENT_WORSTCLIENT_MATH_H
#define GAME_CLIENT_WORSTCLIENT_MATH_H

#include <base/math.h>

#include <algorithm>
#include <numbers>

enum EEaseType
{
	EASE_LINEAR,
	EASE_CUBIC_IN,
	EASE_CUBIC_OUT,
	EASE_COSINE,
};

inline float WorstnessInterpolation(float Value, float Start, float End, EEaseType EaseType)
{
	const float T = std::clamp(Value, 0.0f, 1.0f);
	float Eased = T;
	switch(EaseType)
	{
	case EASE_LINEAR:
		Eased = T;
		break;
	case EASE_CUBIC_IN:
		Eased = T * T * T;
		break;
	case EASE_CUBIC_OUT:
		Eased = 1.0f - (1.0f - T) * (1.0f - T) * (1.0f - T);
		break;
	case EASE_COSINE:
		Eased = (1.0f - std::cos(std::numbers::pi_v<float> * T)) * 0.5f; // the fake pi :omo:
		break;
	}
	return mix(Start, End, Eased);
}

#endif
