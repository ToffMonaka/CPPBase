#include "model_2d.fx"


struct MODEL_SSB_ELEMENT
{
	matrix wvp_mat;
	float4 col;
};


struct MODEL_LAYER_SSB_ELEMENT
{
	uint tex_flg;
	uint dummy1;
	uint dummy2;
	uint dummy3;
	uint2 diffuse_tex_rect_pos;
	uint2 diffuse_tex_rect_size;
};


struct VS_INPUT
{
	float4 pos : POSITION0;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
};


struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 tex_pos : TEXCOORD0;
	uint layer_index : LAYER_INDEX0;
};


struct PS_OUTPUT
{
	float4 col : SV_TARGET0;
};


StructuredBuffer<MODEL_SSB_ELEMENT> model_ssb : MODEL_SSB_SR;
StructuredBuffer<MODEL_LAYER_SSB_ELEMENT> model_layer_ssb : MODEL_LAYER_SSB_SR;
Texture2D<float4> diffuse_tex : USER1_TEX_SR;
SamplerState diffuse_samp : USER1_SAMP_SR;


VS_OUTPUT RunVS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pos = mul(input.pos, model_ssb[0].wvp_mat);
	output.tex_pos = input.tex_pos;
	output.layer_index = input.layer_index;

	return (output);
}


PS_OUTPUT RunPS(VS_OUTPUT input)
{
	PS_OUTPUT output;

	float4 diffuse_col = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	if (model_layer_ssb[input.layer_index].tex_flg & 1) {
		float2 tex_size;

		diffuse_tex.GetDimensions(tex_size.x, tex_size.y);

		float2 tex_pos;

		tex_pos.x = model_layer_ssb[input.layer_index].diffuse_tex_rect_pos.x / tex_size.x + model_layer_ssb[input.layer_index].diffuse_tex_rect_size.x / tex_size.x * input.tex_pos.x;
		tex_pos.y = model_layer_ssb[input.layer_index].diffuse_tex_rect_pos.y / tex_size.y + model_layer_ssb[input.layer_index].diffuse_tex_rect_size.y / tex_size.y * input.tex_pos.y;

		diffuse_col = diffuse_tex.Sample(diffuse_samp, tex_pos);
	}

	output.col = diffuse_col * model_ssb[0].col;

	return (output);
}
