#ifndef __SCREEN_MODEL_UTIL_H__
#define __SCREEN_MODEL_UTIL_H__


#include "constant_util_h.fx"


struct VS_INPUT
{
	float4 pos : POSITION0;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
};


#endif
