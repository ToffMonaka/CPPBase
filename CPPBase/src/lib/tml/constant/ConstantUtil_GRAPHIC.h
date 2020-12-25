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
	const UINT RT_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT DT_LIMIT = 1U;
	const UINT SCB_SR_LIMIT = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	const UINT SCB_UA_SR_LIMIT = 0U;
	const UINT SSB_SR_LIMIT = 16U;
	const UINT SSB_UA_SR_LIMIT = 4U;
	const UINT TEXTURE_SR_LIMIT = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 16U;
	const UINT TEXTURE_UA_SR_LIMIT = D3D11_PS_CS_UAV_REGISTER_COUNT - 4U;
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
}
}
}
