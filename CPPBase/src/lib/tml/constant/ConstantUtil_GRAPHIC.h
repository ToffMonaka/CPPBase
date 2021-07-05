/**
 * @file
 * @brief ConstantUtil_GRAPHICヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#include "ConstantInclude_Direct3DBase.h"


namespace tml {
namespace ConstantUtil {
namespace GRAPHIC {
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		ETC,
		CANVAS,
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
		TEXTURE,
		SAMPLER,
		MODEL,
		FONT,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::COUNT);
	enum class CANVAS_TYPE : UINT {
		NONE = 0U,
		ETC,
		_2D,
		USER,
		COUNT
	};
	const UINT CANVAS_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::COUNT);
	enum class RASTERIZER_STATE_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT RASTERIZER_STATE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_TYPE::COUNT);
	enum class BLEND_STATE_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT BLEND_STATE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::BLEND_STATE_TYPE::COUNT);
	enum class DEPTH_STATE_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT DEPTH_STATE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_TYPE::COUNT);
	enum class SHADER_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT SHADER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_TYPE::COUNT);
	enum class SHADER_CONSTANT_BUFFER_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT SHADER_CONSTANT_BUFFER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_TYPE::COUNT);
	enum class SHADER_STRUCTURED_BUFFER_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT SHADER_STRUCTURED_BUFFER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_TYPE::COUNT);
	enum class CAMERA_TYPE : UINT {
		NONE = 0U,
		ETC,
		PERSPECTIVE,
		ORTHOGRAPHIC,
		USER,
		COUNT
	};
	const UINT CAMERA_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::COUNT);
	enum class LIGHT_TYPE : UINT {
		NONE = 0U,
		ETC,
		AMBIENT,
		DIRECTIONAL,
		POINT,
		SPOT,
		USER,
		COUNT
	};
	const UINT LIGHT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::COUNT);
	enum class FOG_TYPE : UINT {
		NONE = 0U,
		ETC,
		WIDTH,
		HEIGHT,
		USER,
		COUNT
	};
	const UINT FOG_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FOG_TYPE::COUNT);
	enum class MESH_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT MESH_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MESH_TYPE::COUNT);
	enum class TEXTURE_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT TEXTURE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::TEXTURE_TYPE::COUNT);
	enum class SAMPLER_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT SAMPLER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SAMPLER_TYPE::COUNT);
	enum class MODEL_TYPE : UINT {
		NONE = 0U,
		ETC,
		_2D,
		USER,
		COUNT
	};
	const UINT MODEL_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::COUNT);
	enum class FONT_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT FONT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FONT_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::EVENT_TYPE::COUNT);
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
	using SAMPLER_DESC_QUALITY_TYPE = tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE;
	enum class SAMPLER_DESC_WRAP_TYPE : UINT {
		NONE = 0U,
		CC,
		CW,
		WC,
		WW
	};
	const UINT MODEL_2D_INPUT_ELEMENT_DESC_COUNT = 3U;
	const D3D11_INPUT_ELEMENT_DESC MODEL_2D_INPUT_ELEMENT_DESC_ARRAY[tml::ConstantUtil::GRAPHIC::MODEL_2D_INPUT_ELEMENT_DESC_COUNT] = {
		{"POSITION", 0U, DXGI_FORMAT_R32G32B32A32_FLOAT, 0U, 0U, D3D11_INPUT_PER_VERTEX_DATA, 0U},
		{"TEXCOORD", 0U, DXGI_FORMAT_R32G32_FLOAT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
		{"LAYER_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U}
	};
	enum class STRING_ALIGNMENT_TYPE : UINT {
		NONE = 0U,
		LEFT,
		CENTER,
		RIGHT
	};
	enum class POSITION_FIT_TYPE : UINT {
		NONE = 0U,
		CENTER,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};
}
}
}


TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG, UINT)


namespace tml {
namespace graphic {
class Manager;
class Canvas;
class Canvas2D;
class RasterizerState;
class BlendState;
class DepthState;
class Shader;
class ShaderConstantBuffer;
class ConfigShaderConstantBuffer;
class HeaderShaderConstantBuffer;
class ShaderStructuredBuffer;
class CameraShaderStructuredBuffer;
class LightShaderStructuredBuffer;
class FogShaderStructuredBuffer;
class Model2DShaderStructuredBuffer;
class Model2DLayerShaderStructuredBuffer;
class Camera;
class Light;
class Fog;
class Mesh;
class Texture;
class Sampler;
class Model;
class Model2D;
class Font;
}
}
