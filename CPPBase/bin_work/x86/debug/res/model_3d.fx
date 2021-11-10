#include "constant_util_h.fx"


struct CAMERA_SSB_ELEMENT
{
	matrix v_mat;
	matrix inv_v_mat;
	matrix p_mat;
};


struct LIGHT_SSB_ELEMENT
{
	uint dummy1;
	uint dummy2;
	uint dummy3;
	uint dummy4;
};


struct FOG_SSB_ELEMENT
{
	uint dummy1;
	uint dummy2;
	uint dummy3;
	uint dummy4;
};


StructuredBuffer<CAMERA_SSB_ELEMENT> camera_ssb : CAMERA_SSB_SR;
StructuredBuffer<LIGHT_SSB_ELEMENT> light_ssb : LIGHT_SSB_SR;
StructuredBuffer<FOG_SSB_ELEMENT> fog_ssb : FOG_SSB_SR;
