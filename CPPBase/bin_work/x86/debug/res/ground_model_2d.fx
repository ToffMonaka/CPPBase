#include "constant_util_h.fx"


struct MODEL_SSB_ELEMENT
{
	matrix wvp_mat;
	float4 col;
	uint2 tileset_tile_cnt;
	uint dummy1;
	uint dummy2;
};


struct MODEL_LAYER_SSB_ELEMENT
{
	uint diffuse_tex_flg;
	uint dummy1;
	uint dummy2;
	uint dummy3;
};


struct MODEL_BLOCK_SSB_ELEMENT
{
	uint2 tile_cnt;
	uint dummy1;
	uint dummy2;
	uint tile_type_ary[256];
};


struct VS_INPUT
{
	float4 pos : POSITION0;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
	uint block_index : BLOCK_INDEX0;
	uint block_tile_index : BLOCK_TILE_INDEX0;
};


struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
	uint tile_type : TILE_TYPE0;
};


struct PS_OUTPUT
{
	float4 col : SV_TARGET0;
};


StructuredBuffer<MODEL_SSB_ELEMENT> model_ssb : MODEL_SSB_SR;
StructuredBuffer<MODEL_LAYER_SSB_ELEMENT> model_layer_ssb : MODEL_LAYER_SSB_SR;
StructuredBuffer<MODEL_BLOCK_SSB_ELEMENT> model_block_ssb : USER1_SSB_SR;
Texture2D<float4> diffuse_tex : USER1_TEX_SR;
SamplerState diffuse_samp : USER1_SAMP_SR;


VS_OUTPUT RunVS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pos = mul(input.pos, model_ssb[0].wvp_mat);
	output.tex_pos = input.tex_pos;
	output.layer_index = input.layer_index;
	output.tile_type = model_block_ssb[input.block_index].tile_type_ary[input.block_tile_index];

	if (output.tile_type != 0) {
		output.tex_pos.x = (output.tex_pos.x + (uint)((output.tile_type - 1) % model_ssb[0].tileset_tile_cnt.x)) * (1.0f / model_ssb[0].tileset_tile_cnt.x);
		output.tex_pos.y = (output.tex_pos.y + (uint)((output.tile_type - 1) / model_ssb[0].tileset_tile_cnt.x)) * (1.0f / model_ssb[0].tileset_tile_cnt.y);
	}

	return (output);
}


PS_OUTPUT RunPS(VS_OUTPUT input)
{
	if (input.tile_type == 0) {
		discard;
	}

	PS_OUTPUT output;

	float4 diffuse_col = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	if (model_layer_ssb[input.layer_index].diffuse_tex_flg) {
		diffuse_col = diffuse_tex.Sample(diffuse_samp, input.tex_pos);
	}

	output.col = diffuse_col * model_ssb[0].col;

	return (output);
}
