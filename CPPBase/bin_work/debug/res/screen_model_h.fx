#ifndef __SCREEN_MODEL_UTIL_H__
#define __SCREEN_MODEL_UTIL_H__


#include "constant_util_h.fx"


struct MODEL_SSB_ELEMENT
{
	matrix wp_mat;
	float4 col;
};


struct MODEL_LAYER_SSB_ELEMENT
{
	uint diffuse_tex_flg;
	uint dummy1;
	uint dummy2;
	uint dummy3;
};


StructuredBuffer<MODEL_SSB_ELEMENT> model_ssb : MODEL_SSB_SR;
StructuredBuffer<MODEL_LAYER_SSB_ELEMENT> model_layer_ssb : MODEL_LAYER_SSB_SR;
Texture2D<float4> diffuse_tex : USER1_TEX_SR;
SamplerState diffuse_samp : USER1_SAMP_SR;


struct VS_INPUT
{
	float4 pos : POSITION0;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
};


#endif
