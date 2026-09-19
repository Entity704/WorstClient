#ifdef TW_QUAD_TEXTURED
uniform sampler2D gTextureSampler;
#endif

#ifndef TW_QUAD_GROUPED
uniform vec4 gVertColors[TW_MAX_QUADS];
#else
uniform vec4 gVertColors[1];
#endif

noperspective in vec4 QuadColor;
#ifndef TW_QUAD_GROUPED
flat in int QuadIndex;
#else
#define QuadIndex 0
#endif
#ifdef TW_QUAD_TEXTURED
noperspective in vec2 TexCoord;
#endif

uniform float gTime;

const float TEAR_BAND_H = 6.0;
const float TEAR_OFFSET = 0.02;
const float TEAR_CHANCE = 0.30;
const float TEAR_SPEED  = 10.0;

out vec4 FragClr;

float hash11(float p)
{
	p = fract(p * 0.1031);
	p *= p + 33.33;
	p *= p + p;
	return fract(p);
}

void main()
{
#ifdef TW_QUAD_TEXTURED
	vec2 uv = TexCoord;

	float seed = floor(gTime * TEAR_SPEED);

	float band = floor(gl_FragCoord.y / TEAR_BAND_H);

	float r = hash11(band * 1.37 + seed * 7.13);
	if (r > 1.0 - TEAR_CHANCE)
	{
		float dir = hash11(band * 3.71 + seed * 2.53) * 2.0 - 1.0;
		uv.x += dir * TEAR_OFFSET;
	}

	vec4 TexColor = texture(gTextureSampler, uv);
	FragClr = TexColor * QuadColor * gVertColors[QuadIndex];
#else
	FragClr = QuadColor * gVertColors[QuadIndex];
#endif
}