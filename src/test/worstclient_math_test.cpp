#include <game/client/worstclient_math.h>

#include <gtest/gtest.h>

// Deliberately not 0..1, so the tests also catch an implementation that ignores Start and End.
constexpr float TEST_START = -3.0f;
constexpr float TEST_END = 7.0f;
constexpr float TEST_RANGE = TEST_END - TEST_START;

constexpr EEaseType ALL_EASE_TYPES[] = {EASE_LINEAR, EASE_CUBIC_IN, EASE_CUBIC_OUT, EASE_COSINE};

TEST(WorstnessInterpolation, Endpoints)
{
	for(const EEaseType Ease : ALL_EASE_TYPES)
	{
		EXPECT_NEAR(TEST_START, WorstnessInterpolation(0.0f, TEST_START, TEST_END, Ease), 0.0001f);
		EXPECT_NEAR(TEST_END, WorstnessInterpolation(1.0f, TEST_START, TEST_END, Ease), 0.0001f);
	}
}

TEST(WorstnessInterpolation, ClampsValue)
{
	for(const EEaseType Ease : ALL_EASE_TYPES)
	{
		EXPECT_NEAR(TEST_START, WorstnessInterpolation(-1.0f, TEST_START, TEST_END, Ease), 0.0001f);
		EXPECT_NEAR(TEST_END, WorstnessInterpolation(2.0f, TEST_START, TEST_END, Ease), 0.0001f);
	}
}

TEST(WorstnessInterpolation, Midpoint)
{
	// All four curves are symmetric around their midpoint.
	for(const EEaseType Ease : ALL_EASE_TYPES)
	{
		EXPECT_NEAR((TEST_START + TEST_END) * 0.5f, WorstnessInterpolation(0.5f, TEST_START, TEST_END, Ease), 0.0001f);
	}
}

TEST(WorstnessInterpolation, CurveShape)
{
	constexpr float Value = 0.25f;
	EXPECT_NEAR(TEST_START + TEST_RANGE * 0.25f, WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_LINEAR), 0.0001f);
	EXPECT_NEAR(TEST_START + TEST_RANGE * 0.015625f, WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_CUBIC_IN), 0.0001f); // 0.25^3
	EXPECT_NEAR(TEST_START + TEST_RANGE * 0.578125f, WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_CUBIC_OUT), 0.0001f); // 1 - 0.75^3
	EXPECT_NEAR(TEST_START + TEST_RANGE * 0.14644661f, WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_COSINE), 0.0001f); // (1 - cos(pi/4)) / 2
}

TEST(WorstnessInterpolation, CurvesDiffer)
{
	// Catch an implementation where every curve degenerates into the same one.
	constexpr float Value = 0.25f;
	EXPECT_NE(WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_LINEAR), WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_CUBIC_IN));
	EXPECT_NE(WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_CUBIC_IN), WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_CUBIC_OUT));
	EXPECT_NE(WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_CUBIC_OUT), WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_COSINE));
	EXPECT_NE(WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_COSINE), WorstnessInterpolation(Value, TEST_START, TEST_END, EASE_LINEAR));
}
