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
	const UINT RENDER_TARGET_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT DEPTH_TARGET_LIMIT = 1U;
	const UINT SHADER_CONSTANT_BUFFER_SR_LIMIT = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	const UINT SHADER_CONSTANT_BUFFER_UASR_LIMIT = 0U;
	const UINT SHADER_STRUCTURED_BUFFER_SR_LIMIT = 16U;
	const UINT SHADER_STRUCTURED_BUFFER_UASR_LIMIT = 4U;
	const UINT TEXTURE_SR_LIMIT = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 16U;
	const UINT TEXTURE_UASR_LIMIT = D3D11_PS_CS_UAV_REGISTER_COUNT - 4U;
	const UINT SAMPLER_SR_LIMIT = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;
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
		DEFAULT,
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
	enum class TEXTURE_DESC_TYPE_FLAG : UINT {
		NONE = 0U,
		RENDER_TARGET = 1U << 0,
		DEPTH_TARGET = 1U << 1,
		SR = 1U << 2,
		UASR = 1U << 3
	};
	enum class SAMPLER_DESC_TYPE : UINT {
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
}
}
}


ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG, UINT)
