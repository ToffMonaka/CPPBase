#include "sprite_model_h.fx"


struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
};


struct PS_OUTPUT
{
	float4 diffuse_col : SV_TARGET0;
};


VS_OUTPUT RunVS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pos = input.pos.x * model_ssb[0].wvp_mat[0] + input.pos.y * model_ssb[0].wvp_mat[1] + input.pos.z * model_ssb[0].wvp_mat[2] + input.pos.w * model_ssb[0].wvp_mat[3];

	return (output);
}


PS_OUTPUT RunPS(VS_OUTPUT input)
{
	PS_OUTPUT output;

	output.diffuse_col = float4(1.0, 0.0, 0.0, 1.0);

	return (output);
}
