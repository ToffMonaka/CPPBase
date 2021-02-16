#ifndef __SPRITE_MODEL_UTIL_H__
#define __SPRITE_MODEL_UTIL_H__


#include "constant_util_h.fx"


Texture2D<float4> diffuse_tex : USER1_TEX_SR;
SamplerState diffuse_samp : USER1_SAMP_SR;


struct VS_INPUT
{
	float4 pos : POSITION0;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
};


#endif
