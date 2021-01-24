/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
class RasterizerState;
class BlendState;
class DepthState;
class Shader;
class LightShaderConstantBuffer;
class FogShaderConstantBuffer;
class ShadowShaderConstantBuffer;
class AOShaderConstantBuffer;
class ModelShaderConstantBuffer;
class CameraShaderStructuredBuffer;
class LightShaderStructuredBuffer;
class FogShaderStructuredBuffer;
class ShadowShaderStructuredBuffer;
class ShadowCameraShaderStructuredBuffer;
class ModelLayerShaderStructuredBuffer;
class ModelMatrixShaderStructuredBuffer;
class ModelMaterialShaderStructuredBuffer;
class Texture;
class Sampler;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerCommonクラス
 */
class ManagerCommon
{
public: ManagerCommon(const tml::graphic::ManagerCommon &) = delete;
public: tml::graphic::ManagerCommon &operator =(const tml::graphic::ManagerCommon &) = delete;

public:
	tml::shared_ptr<tml::graphic::RasterizerState> default_rasterizer_state;
	tml::shared_ptr<tml::graphic::RasterizerState> wireframe_rasterizer_state;
	tml::shared_ptr<tml::graphic::RasterizerState> front_culling_rasterizer_state;
	tml::shared_ptr<tml::graphic::RasterizerState> back_culling_rasterizer_state;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> default_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> alignment_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> add_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> sub_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> mul_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> reverse_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, 2U> total_blend_state_array;
	tml::shared_ptr<tml::graphic::DepthState> default_depth_state;
	tml::shared_ptr<tml::graphic::DepthState> reference_depth_state;
	tml::shared_ptr<tml::graphic::Shader> screen_model_shader;
	tml::shared_ptr<tml::graphic::Shader> sprite_model_shader;
	tml::shared_ptr<tml::graphic::LightShaderConstantBuffer> light_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::FogShaderConstantBuffer> fog_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::ShadowShaderConstantBuffer> shadow_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::AOShaderConstantBuffer> ao_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::ModelShaderConstantBuffer> model_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::CameraShaderStructuredBuffer> camera_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::LightShaderStructuredBuffer> light_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::FogShaderStructuredBuffer> fog_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::ShadowShaderStructuredBuffer> shadow_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::ShadowCameraShaderStructuredBuffer> shadow_camera_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::ModelLayerShaderStructuredBuffer> model_layer_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::ModelMatrixShaderStructuredBuffer> model_matrix_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::ModelMaterialShaderStructuredBuffer> model_material_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Texture> main_render_target_texture;
	tml::shared_ptr<tml::graphic::Texture> main_depth_target_texture;
	tml::shared_ptr<tml::graphic::Sampler> model_cc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> model_cw_sampler;
	tml::shared_ptr<tml::graphic::Sampler> model_wc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> model_ww_sampler;

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}
