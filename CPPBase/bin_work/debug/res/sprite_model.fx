#include "sprite_model_h.fx"


struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
};


struct PS_OUTPUT
{
	float4 col : SV_TARGET0;
};


VS_OUTPUT RunVS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pos = mul(mul(input.pos, model_ssb[0].w_mat), camera_ssb[1].p_mat);

	return (output);
}


PS_OUTPUT RunPS(VS_OUTPUT input)
{
	PS_OUTPUT output;

	output.col = float4(1.0, 0.0, 0.0, 1.0);

	return (output);
}
