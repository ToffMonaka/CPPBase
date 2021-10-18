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
	namespace CLASS_NAME {
	}
	namespace RESOURCE_NAME {
	}
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		BASE,
		RASTERIZER_STATE,
		BLEND_STATE,
		DEPTH_STATE,
		SHADER,
		SHADER_CONSTANT_BUFFER,
		SHADER_STRUCTURED_BUFFER,
		MESH,
		TEXTURE,
		SAMPLER,
		FONT,
		ATLAS,
		MAP,
		CANVAS,
		CAMERA,
		LIGHT,
		FOG,
		MODEL,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::COUNT);
	enum class RASTERIZER_STATE_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT RASTERIZER_STATE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_TYPE::COUNT);
	enum class BLEND_STATE_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT BLEND_STATE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::BLEND_STATE_TYPE::COUNT);
	enum class DEPTH_STATE_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT DEPTH_STATE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_TYPE::COUNT);
	enum class SHADER_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT SHADER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_TYPE::COUNT);
	enum class SHADER_CONSTANT_BUFFER_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT SHADER_CONSTANT_BUFFER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_TYPE::COUNT);
	enum class SHADER_STRUCTURED_BUFFER_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT SHADER_STRUCTURED_BUFFER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_TYPE::COUNT);
	enum class MESH_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT MESH_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MESH_TYPE::COUNT);
	enum class TEXTURE_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT TEXTURE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::TEXTURE_TYPE::COUNT);
	enum class SAMPLER_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT SAMPLER_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SAMPLER_TYPE::COUNT);
	enum class FONT_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT FONT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FONT_TYPE::COUNT);
	enum class ATLAS_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT ATLAS_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::ATLAS_TYPE::COUNT);
	enum class MAP_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT MAP_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MAP_TYPE::COUNT);
	enum class CANVAS_TYPE : UINT {
		NONE = 0U,
		BASE,
		_2D,
		_3D,
		USER,
		COUNT
	};
	const UINT CANVAS_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::COUNT);
	enum class CAMERA_TYPE : UINT {
		NONE = 0U,
		BASE,
		_2D,
		_3D,
		USER,
		COUNT
	};
	const UINT CAMERA_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::COUNT);
	enum class LIGHT_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT LIGHT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::COUNT);
	enum class FOG_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT FOG_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FOG_TYPE::COUNT);
	enum class MODEL_TYPE : UINT {
		NONE = 0U,
		BASE,
		_2D,
		_3D,
		USER,
		COUNT
	};
	const UINT MODEL_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		BASE,
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
	const UINT RENDER_TARGET_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT DEPTH_TARGET_LIMIT = 1U;
	const UINT VIEWPORT_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT SHADER_CONSTANT_BUFFER_SR_LIMIT = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	const UINT SHADER_STRUCTURED_BUFFER_SR_LIMIT = 16U;
	const UINT SHADER_STRUCTURED_BUFFER_UASR_LIMIT = 4U;
	const UINT TEXTURE_SR_LIMIT = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 16U;
	const UINT TEXTURE_UASR_LIMIT = D3D11_PS_CS_UAV_REGISTER_COUNT - 4U;
	const UINT SAMPLER_SR_LIMIT = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;
	const UINT CANVAS_LIMIT = 128U;
	const UINT CAMERA_LIMIT = 128U;
	const UINT LIGHT_LIMIT = 128U;
	const UINT FOG_LIMIT = 128U;
	const UINT MODEL_LIMIT = 128U;
	enum class DRAW_STAGE_TYPE : UINT {
		NONE = 0U,
		INIT,
		DEFERRED_3D,
		DEFERRED_3D_SHADOW,
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
	enum class CAMERA_2D_PROJECTION_TYPE : UINT {
		NONE = 0U,
		ORTHOGRAPHIC
	};
	enum class CAMERA_3D_PROJECTION_TYPE : UINT {
		NONE = 0U,
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	enum class LIGHT_EFFECT_TYPE : UINT {
		NONE = 0U,
		AMBIENT,
		DIRECTIONAL,
		POINT,
		SPOT
	};
	enum class FOG_EFFECT_TYPE : UINT {
		NONE = 0U,
		WIDTH,
		HEIGHT
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
class RasterizerState;
class RasterizerStateDesc;
class BlendState;
class BlendStateDesc;
class DepthState;
class DepthStateDesc;
class Shader;
class ShaderDesc;
class ShaderConstantBuffer;
class ShaderConstantBufferDesc;
class ConfigShaderConstantBuffer;
class ConfigShaderConstantBufferDesc;
class HeaderShaderConstantBuffer;
class HeaderShaderConstantBufferDesc;
class ShaderStructuredBuffer;
class ShaderStructuredBufferDesc;
class CameraShaderStructuredBuffer;
class CameraShaderStructuredBufferDesc;
class LightShaderStructuredBuffer;
class LightShaderStructuredBufferDesc;
class FogShaderStructuredBuffer;
class FogShaderStructuredBufferDesc;
class FigureModel2DShaderStructuredBuffer;
class FigureModel2DShaderStructuredBufferDesc;
class FigureModel2DLayerShaderStructuredBuffer;
class FigureModel2DLayerShaderStructuredBufferDesc;
class GroundModel2DShaderStructuredBuffer;
class GroundModel2DShaderStructuredBufferDesc;
class GroundModel2DLayerShaderStructuredBuffer;
class GroundModel2DLayerShaderStructuredBufferDesc;
class GroundModel2DBlockShaderStructuredBuffer;
class GroundModel2DBlockShaderStructuredBufferDesc;
class Mesh;
class MeshDesc;
class Texture;
class TextureDesc;
class Sampler;
class SamplerDesc;
class Font;
class FontDesc;
class Atlas;
class AtlasDesc;
class Map;
class MapDesc;
class Canvas;
class CanvasDesc;
class Canvas2D;
class Canvas2DDesc;
class Camera;
class CameraDesc;
class Camera2D;
class Camera2DDesc;
class Camera3D;
class Camera3DDesc;
class Light;
class LightDesc;
class Fog;
class FogDesc;
class Model;
class ModelDesc;
class Model2D;
class Model2DDesc;
class FigureModel2D;
class FigureModel2DDesc;
class GroundModel2D;
class GroundModel2DDesc;
}
}
