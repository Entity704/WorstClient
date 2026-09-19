#version 450
#extension GL_ARB_separate_shader_objects : enable

#ifdef TW_QUAD_TEXTURED
layout (set = 0, binding = 0) uniform sampler2D gTextureSampler;
#endif

#ifdef TW_QUAD_TEXTURED
#define UBOSetIndex 1
#else
#define UBOSetIndex 0
#endif

struct SQuadUniformEl {
	vec4 gVertColor;
	vec2 gOffset;
	float gRotation;
};

#ifndef TW_QUAD_GROUPED
#define TW_MAX_QUADS 256

layout (std140, set = UBOSetIndex, binding = 1) uniform SOffBO {
	uniform SQuadUniformEl gUniEls[TW_MAX_QUADS];
} gQuadBO;
#else
#define gQuadBO gPosBO
#define QuadIndex 0
#endif

layout (std140, set = UBOSetIndex, binding = 2) uniform STimeBO {
	float gTime;
} gTimeBO;

const float TEAR_BAND_H = 6.0;
const float TEAR_OFFSET = 0.02;
const float TEAR_CHANCE = 0.30;
const float TEAR_SPEED  = 10.0;

layout(push_constant) uniform SPosBO {
	layout(offset = 0) uniform mat4x2 gPos;
#ifdef TW_QUAD_GROUPED
	layout(offset = 32) uniform SQuadUniformEl gUniEls[1];
#else
	layout(offset = 32) uniform int gQuadOffset;
#endif
} gPosBO;

layout (location = 0) noperspective in vec4 QuadColor;
#ifndef TW_QUAD_GROUPED
layout (location = 1) flat in int QuadIndex;
#endif
#ifdef TW_QUAD_TEXTURED
#ifndef TW_QUAD_GROUPED
layout (location = 2) noperspective in vec2 TexCoord;
#else
layout (location = 1) noperspective in vec2 TexCoord;
#endif
#endif

layout (location = 0) out vec4 FragClr;

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

	float seed = floor(gTimeBO.gTime * TEAR_SPEED);

	float band = floor(gl_FragCoord.y / TEAR_BAND_H);

	float r = hash11(band * 1.37 + seed * 7.13);
	if (r > 1.0 - TEAR_CHANCE)
	{
		float dir = hash11(band * 3.71 + seed * 2.53) * 2.0 - 1.0;
		uv.x += dir * TEAR_OFFSET;
	}

	vec4 TexColor = texture(gTextureSampler, uv);
	FragClr = TexColor * QuadColor * gQuadBO.gUniEls[QuadIndex].gVertColor;
#else
	FragClr = QuadColor * gQuadBO.gUniEls[QuadIndex].gVertColor;
#endif
}
