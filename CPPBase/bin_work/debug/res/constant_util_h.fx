#ifndef __CONSTANT_UTIL_H__
#define __CONSTANT_UTIL_H__


// SHADER_CONSTANT_BUFFER_SR_LIMIT 14
#define CONF_SCB_SR register(b0)
#define HEAD_SCB_SR register(b1)
#define USER1_SCB_SR register(b2)
#define USER2_SCB_SR register(b3)
#define USER3_SCB_SR register(b4)
#define USER4_SCB_SR register(b5)
#define USER5_SCB_SR register(b6)
#define USER6_SCB_SR register(b7)
#define USER7_SCB_SR register(b8)
#define USER8_SCB_SR register(b9)
#define USER9_SCB_SR register(b10)
#define USER10_SCB_SR register(b11)
#define USER11_SCB_SR register(b12)
#define USER12_SCB_SR register(b13)

// SHADER_STRUCTURED_BUFFER_SR_LIMIT 16
#define CAMERA_SSB_SR register(t112)
#define LIGHT_SSB_SR register(t113)
#define FOG_SSB_SR register(t114)
#define MODEL_SSB_SR register(t115)
#define MODEL_LAYER_SSB_SR register(t116)
#define USER1_SSB_SR register(t117)
#define USER2_SSB_SR register(t118)
#define USER3_SSB_SR register(t119)
#define USER4_SSB_SR register(t120)
#define USER5_SSB_SR register(t121)
#define USER6_SSB_SR register(t122)
#define USER7_SSB_SR register(t123)
#define USER8_SSB_SR register(t124)
#define USER9_SSB_SR register(t125)
#define USER10_SSB_SR register(t126)
#define USER11_SSB_SR register(t127)

// SHADER_STRUCTURED_BUFFER_UASR_LIMIT 4
#define USER1_SSB_UASR register(u4)
#define USER2_SSB_UASR register(u5)
#define USER3_SSB_UASR register(u6)
#define USER4_SSB_UASR register(u7)

// TEXTURE_SR_LIMIT 112
#define USER1_TEX_SR register(t0)
#define USER2_TEX_SR register(t1)
#define USER3_TEX_SR register(t2)
#define USER4_TEX_SR register(t3)
#define USER5_TEX_SR register(t4)
#define USER6_TEX_SR register(t5)
#define USER7_TEX_SR register(t6)
#define USER8_TEX_SR register(t7)
#define USER9_TEX_SR register(t8)
#define USER10_TEX_SR register(t9)
#define USER11_TEX_SR register(t10)
#define USER12_TEX_SR register(t11)
#define USER13_TEX_SR register(t12)
#define USER14_TEX_SR register(t13)
#define USER15_TEX_SR register(t14)
#define USER16_TEX_SR register(t15)
#define USER17_TEX_SR register(t16)
#define USER18_TEX_SR register(t17)
#define USER19_TEX_SR register(t18)
#define USER20_TEX_SR register(t19)
#define USER21_TEX_SR register(t20)
#define USER22_TEX_SR register(t21)
#define USER23_TEX_SR register(t22)
#define USER24_TEX_SR register(t23)
#define USER25_TEX_SR register(t24)
#define USER26_TEX_SR register(t25)
#define USER27_TEX_SR register(t26)
#define USER28_TEX_SR register(t27)
#define USER29_TEX_SR register(t28)
#define USER30_TEX_SR register(t29)
#define USER31_TEX_SR register(t30)
#define USER32_TEX_SR register(t31)

// TEXTURE_UASR_LIMIT 4
#define USER1_TEX_UASR register(u0)
#define USER2_TEX_UASR register(u1)
#define USER3_TEX_UASR register(u2)
#define USER4_TEX_UASR register(u3)

// SAMPLER_SR_LIMIT 16
#define USER1_SAMP_SR register(s0)
#define USER2_SAMP_SR register(s1)
#define USER3_SAMP_SR register(s2)
#define USER4_SAMP_SR register(s3)
#define USER5_SAMP_SR register(s4)
#define USER6_SAMP_SR register(s5)
#define USER7_SAMP_SR register(s6)
#define USER8_SAMP_SR register(s7)
#define USER9_SAMP_SR register(s8)
#define USER10_SAMP_SR register(s9)
#define USER11_SAMP_SR register(s10)
#define USER12_SAMP_SR register(s11)
#define USER13_SAMP_SR register(s12)
#define USER14_SAMP_SR register(s13)
#define USER15_SAMP_SR register(s14)
#define USER16_SAMP_SR register(s15)


cbuffer CONF_SCB : CONF_SCB_SR
{
	uint conf_scb_dummy1;
	uint conf_scb_dummy2;
	uint conf_scb_dummy3;
	uint conf_scb_dummy4;
};


cbuffer HEAD_SCB : HEAD_SCB_SR
{
	uint head_scb_camera_cnt;
	uint head_scb_light_cnt;
	uint head_scb_fog_cnt;
	uint head_scb_model_cnt;
};


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


struct MODEL_SSB_ELEMENT
{
	matrix w_mat;
};


struct MODEL_LAYER_SSB_ELEMENT
{
	uint dummy1;
	uint dummy2;
	uint dummy3;
	uint dummy4;
};


StructuredBuffer<CAMERA_SSB_ELEMENT> camera_ssb : CAMERA_SSB_SR;
StructuredBuffer<LIGHT_SSB_ELEMENT> light_ssb : LIGHT_SSB_SR;
StructuredBuffer<FOG_SSB_ELEMENT> fog_ssb : FOG_SSB_SR;
StructuredBuffer<MODEL_SSB_ELEMENT> model_ssb : MODEL_SSB_SR;
StructuredBuffer<MODEL_LAYER_SSB_ELEMENT> model_layer_ssb : MODEL_LAYER_SSB_SR;


#endif
