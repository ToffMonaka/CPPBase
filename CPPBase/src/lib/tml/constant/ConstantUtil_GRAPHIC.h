/**
 * @file
 * @brief ConstantUtil_GRAPHICヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#pragma warning(pop)


namespace tml {
namespace ConstantUtil {
namespace GRAPHIC {
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		RASTERIZER_STATE,
		BLEND_STATE,
		DEPTH_STATE,
		SHADER,
		SHADER_CONSTANT_BUFFER,
		SHADER_STRUCTURED_BUFFER,
		CAMERA,
		LIGHT,
		FOG,
		MESH,
		MATERIAL,
		TEXTURE,
		SAMPLER,
		MODEL,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::COUNT);
	enum class SAMPLER_QUALITY_TYPE : UINT {
		NONE = 0U,
		BILINEAR,
		TRILINEAR,
		ANISOTROPIC2,
		ANISOTROPIC4,
		ANISOTROPIC8,
		ANISOTROPIC16
	};
	enum class MOTION_QUALITY_TYPE : UINT {
		NONE = 0U,
		LOW,
		MEDIUM
	};
	enum class SHADOW_QUALITY_TYPE : UINT {
		NONE = 0U,
		MEDIUM
	};
	enum class AO_QUALITY_TYPE : UINT {
		NONE = 0U,
		MEDIUM
	};
	enum class BLOOM_QUALITY_TYPE : UINT {
		NONE = 0U,
		MEDIUM
	};
	enum class AA_QUALITY_TYPE : UINT {
		NONE = 0U,
		FXAA
	};
	const UINT VIEWPORT_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT RENDER_TARGET_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT DEPTH_TARGET_LIMIT = 1U;
	const UINT SHADER_CONSTANT_BUFFER_SR_LIMIT = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	const UINT SHADER_STRUCTURED_BUFFER_SR_LIMIT = 16U;
	const UINT SHADER_STRUCTURED_BUFFER_UASR_LIMIT = 4U;
	const UINT CAMERA_LIMIT = 2U;
	const UINT LIGHT_LIMIT = 128U;
	const UINT FOG_LIMIT = 16U;
	const UINT TEXTURE_SR_LIMIT = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 16U;
	const UINT TEXTURE_UASR_LIMIT = D3D11_PS_CS_UAV_REGISTER_COUNT - 4U;
	const UINT SAMPLER_SR_LIMIT = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;
	const UINT MODEL_LIMIT = 256U;
	enum class RASTERIZER_STATE_DESC_TYPE : UINT {
		NONE = 0U,
		DEFAULT,
		WIREFRAME,
		FRONT_CULLING,
		BACK_CULLING
	};
	enum class BLEND_STATE_DESC_TYPE : UINT {
		NONE = 0U,
		DEFAULT,
		ALIGNMENT,
		ADD,
		SUB,
		MUL,
		REVERSE,
		TOTAL
	};
	enum class BLEND_STATE_DESC_ALPHA_TYPE : UINT {
		NONE = 0U,
		SRC,
		DST,
		TOTAL
	};
	const UINT BLEND_STATE_FACTOR_COUNT = 4U;
	enum class DEPTH_STATE_DESC_TYPE : UINT {
		NONE = 0U,
		DEFAULT,
		REFERENCE
	};
	enum class SHADER_TYPE : UINT {
		NONE = 0U,
		VERTEX_,
		HULL_,
		DOMAIN_,
		GEOMETRY_,
		PIXEL_,
		COMPUTE_
	};
	enum class SHADER_TYPE_FLAG : UINT {
		NONE = 0U,
		VERTEX_ = 1U << 0,
		HULL_ = 1U << 1,
		DOMAIN_ = 1U << 2,
		GEOMETRY_ = 1U << 3,
		PIXEL_ = 1U << 4,
		COMPUTE_ = 1U << 5
	};
	enum class SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG : UINT {
		NONE = 0U,
		SR = 1U << 0
	};
	namespace SHADER_CONSTANT_BUFFER_SR_INDEX {
	enum : UINT {
		SYSTEM = 0U,
		CONFIG = 0U,
		HEADER,
		USER
	};
	}
	enum class SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG : UINT {
		NONE = 0U,
		SR = 1U << 0,
		UASR = 1U << 1
	};
	namespace SHADER_STRUCTURED_BUFFER_INDEX {
	enum : UINT {
		SYSTEM = 0U,
		CAMERA = 0U,
		LIGHT,
		FOG,
		MODEL,
		MODEL_LAYER,
		USER
	};
	}
	enum class CAMERA_TYPE : UINT {
		NONE = 0U,
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	enum class LIGHT_TYPE : UINT {
		NONE = 0U,
		AMBIENT,
		DIRECTIONAL,
		POINT,
		SPOT
	};
	enum class FOG_TYPE : UINT {
		NONE = 0U,
		WIDTH,
		HEIGHT
	};
	enum class TEXTURE_DESC_BIND_FLAG : UINT {
		NONE = 0U,
		RENDER_TARGET = 1U << 0,
		DEPTH_TARGET = 1U << 1,
		SR = 1U << 2,
		UASR = 1U << 3
	};
	enum class SAMPLER_DESC_BIND_FLAG : UINT {
		NONE = 0U,
		SR = 1U << 0
	};
	enum class SAMPLER_DESC_QUALITY_TYPE : UINT {
		NONE = 0U,
		BILINEAR,
		TRILINEAR,
		ANISOTROPIC2,
		ANISOTROPIC4,
		ANISOTROPIC8,
		ANISOTROPIC16
	};
	enum class SAMPLER_DESC_WRAP_TYPE : UINT {
		NONE = 0U,
		CC,
		CW,
		WC,
		WW
	};
	enum class MODEL_TYPE : UINT {
		NONE = 0U,
		SCREEN,
		SPRITE
	};
	const UINT SCREEN_MODEL_INPUT_ELEMENT_DESC_COUNT = 3U;
	const D3D11_INPUT_ELEMENT_DESC SCREEN_MODEL_INPUT_ELEMENT_DESC_ARRAY[tml::ConstantUtil::GRAPHIC::SCREEN_MODEL_INPUT_ELEMENT_DESC_COUNT] = {
		{"POSITION", 0U, DXGI_FORMAT_R32G32B32A32_FLOAT, 0U, 0U, D3D11_INPUT_PER_VERTEX_DATA, 0U},
		{"TEXCOORD", 0U, DXGI_FORMAT_R32G32_FLOAT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
		{"LAYER_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U}
	};
	const UINT SPRITE_MODEL_INPUT_ELEMENT_DESC_COUNT = 3U;
	const D3D11_INPUT_ELEMENT_DESC SPRITE_MODEL_INPUT_ELEMENT_DESC_ARRAY[tml::ConstantUtil::GRAPHIC::SPRITE_MODEL_INPUT_ELEMENT_DESC_COUNT] = {
		{"POSITION", 0U, DXGI_FORMAT_R32G32B32A32_FLOAT, 0U, 0U, D3D11_INPUT_PER_VERTEX_DATA, 0U},
		{"TEXCOORD", 0U, DXGI_FORMAT_R32G32_FLOAT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
		{"LAYER_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U}
	};
	enum class DRAW_STAGE_TYPE : UINT {
		NONE = 0U,
		INIT,
		DEFERRED_3D,
		DEFERRED_SHADOW_3D,
		FORWARD_3D,
		FORWARD_2D,
		COUNT
	};
	const UINT DRAW_STAGE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::COUNT);
}
}
}


TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG, UINT)
