#include "figure_model_2d_h.fx"


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
	
	if (model_layer_ssb[input.layer_index].diffuse_tex_flg) {
		diffuse_col = diffuse_tex.Sample(diffuse_samp, input.tex_pos);
	}

	output.col = diffuse_col * model_ssb[0].col;

	return (output);
}
