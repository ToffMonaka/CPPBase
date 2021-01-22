#include "sprite_model_h.fx"


struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 tex_pos : TEXCOORD0;
	uint material_index : MATERIAL_INDEX0;
	uint samp_index : SAMP_INDEX0;
};


struct PS_OUTPUT
{
	float4 diffuse_col : SV_TARGET0;
};


VS_OUTPUT RunVS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pos = input.pos;
	output.tex_pos = input.tex_pos;
	output.material_index = 0;
	output.samp_index = 0;

	return (output);
}


PS_OUTPUT RunPS(VS_OUTPUT input)
{
	PS_OUTPUT output;

	output.diffuse_col = float4(0.0, 0.0, 0.0, 1.0);

	return (output);
}
