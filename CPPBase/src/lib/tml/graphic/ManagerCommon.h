/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
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
class ShaderConstantBuffer;
class ConfigShaderConstantBuffer;
class ModelShaderConstantBuffer;
class ShaderStructuredBuffer;
class CameraShaderStructuredBuffer;
class LightShaderStructuredBuffer;
class FogShaderStructuredBuffer;
class ModelLayerShaderStructuredBuffer;
class Camera;
class Light;
class Fog;
class Mesh;
class Material;
class Texture;
class Sampler;
class Model;
class ScreenModel;
class SpriteModel;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const tml::graphic::ManagerCommon &) = delete;
public: tml::graphic::ManagerCommon &operator =(const tml::graphic::ManagerCommon &) = delete;

private:
	tml::graphic::Manager *mgr_;

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
	tml::shared_ptr<tml::graphic::ConfigShaderConstantBuffer> config_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::CameraShaderStructuredBuffer> camera_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::LightShaderStructuredBuffer> light_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::FogShaderStructuredBuffer> fog_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Texture> main_render_target_texture;
	tml::shared_ptr<tml::graphic::Texture> main_depth_target_texture;
	tml::shared_ptr<tml::graphic::Sampler> model_cc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> model_cw_sampler;
	tml::shared_ptr<tml::graphic::Sampler> model_wc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> model_ww_sampler;

private:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}
