layout (location = 0) in vec2 inVertex;
layout (location = 1) in vec2 inVertexTexCoord;
layout (location = 2) in vec4 inVertexColor;

uniform mat4x2 gPos;
uniform float gTextureSize;

noperspective out vec2 texCoord;
noperspective out vec4 outVertColor;

#define TW_TEXT_GLITCH_BANDS 32.0
#define TW_TEXT_GLITCH_BANDS_Y 32.0
#define TW_TEXT_GLITCH_AMOUNT_X 0.016
#define TW_TEXT_GLITCH_AMOUNT_Y 0.016
#define TW_TEXT_GLITCH_SHARPNESS 0.4

float GlitchHash(float p)
{
	p = fract(p * 0.1031);
	p *= p + 33.33;
	p *= p + p;
	return fract(p);
}

float GlitchWarp(float ClipY)
{
	return ClipY + 0.06 * sin(ClipY * 4.1 + 1.7) + 0.03 * sin(ClipY * 9.7 + 0.4);
}

float GlitchOffset(float Coord, float Bands, float Seed)
{
	float Band = GlitchWarp(Coord) * Bands;
	float Index = floor(Band);
	float Amount = GlitchHash(Index * 1.31 + Seed) * 2.0 - 1.0;
	float Strength = GlitchHash(Index * 0.77 + Seed + 19.3);
	Strength = 0.3 + 0.7 * Strength * Strength;
	float Window = pow(max(sin(fract(Band) * 3.14159265), 0.0), TW_TEXT_GLITCH_SHARPNESS);
	return Amount * Strength * Window;
}

void main()
{
	vec2 ClipPos = gPos * vec4(inVertex, 0.0, 1.0);
	ClipPos.x += GlitchOffset(ClipPos.y, TW_TEXT_GLITCH_BANDS, 11.0) * TW_TEXT_GLITCH_AMOUNT_X;
	ClipPos.y += GlitchOffset(ClipPos.x, TW_TEXT_GLITCH_BANDS_Y, 53.0) * TW_TEXT_GLITCH_AMOUNT_Y;
	gl_Position = vec4(ClipPos, 0.0, 1.0);

	texCoord = vec2(inVertexTexCoord.x / gTextureSize, inVertexTexCoord.y / gTextureSize);
	outVertColor = inVertexColor;
}
