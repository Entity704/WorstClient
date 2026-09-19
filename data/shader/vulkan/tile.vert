#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec2 inVertex;
#ifdef TW_TILE_TEXTURED
layout (location = 1) in uvec4 inVertexTexCoord;
#endif

layout(push_constant) uniform SPosBO {
	layout(offset = 0) uniform mat4x2 gPos;
} gPosBO;

#ifdef TW_TILE_TEXTURED
layout (location = 0) noperspective out vec3 TexCoord;
#endif

#define TW_GLITCH_BANDS 26.0
#define TW_GLITCH_BANDS_Y 26.0
#define TW_GLITCH_AMOUNT_X 0.0042
#define TW_GLITCH_AMOUNT_Y 0.0042
#define TW_GLITCH_SHARPNESS 0.4

float GlitchHash(float p)
{
	p = fract(p * 0.1031);
	p *= p + 33.33;
	p *= p + p;
	return fract(p);
}

// Warps the band coordinate so the bands are not evenly spaced: some get
// squeezed together, some stretched out.
float GlitchWarp(float ClipY)
{
	return ClipY + 0.06 * sin(ClipY * 4.1 + 1.7) + 0.03 * sin(ClipY * 9.7 + 0.4);
}

// Most bands keep only a small offset while a few tear hard, and the seed
// keeps the x and y offsets independent of each other.
float GlitchOffset(float Coord, float Bands, float Seed)
{
	float Band = GlitchWarp(Coord) * Bands;
	float Index = floor(Band);
	float Amount = GlitchHash(Index * 1.31 + Seed) * 2.0 - 1.0;
	float Strength = GlitchHash(Index * 0.77 + Seed + 19.3);
	Strength = 0.3 + 0.7 * Strength * Strength;
	float Window = pow(max(sin(fract(Band) * 3.14159265), 0.0), TW_GLITCH_SHARPNESS);
	return Amount * Strength * Window;
}

void main()
{
	vec2 ClipPos = gPosBO.gPos * vec4(inVertex, 0.0, 1.0);
	// Each offset is banded along the *other* axis: that is what makes lines
	// running perpendicular to it break up. Banding the vertical offset along
	// y would only move whole rows up and down, which is invisible.
	ClipPos.x += GlitchOffset(ClipPos.y, TW_GLITCH_BANDS, 0.0) * TW_GLITCH_AMOUNT_X;
	ClipPos.y += GlitchOffset(ClipPos.x, TW_GLITCH_BANDS_Y, 37.0) * TW_GLITCH_AMOUNT_Y;
	gl_Position = vec4(ClipPos, 0.0, 1.0);

#ifdef TW_TILE_TEXTURED
	TexCoord = vec3(inVertexTexCoord.xyz);
#endif
}
