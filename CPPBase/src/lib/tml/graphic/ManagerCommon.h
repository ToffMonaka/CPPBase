/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerCommonクラス
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
	tml::shared_ptr<tml::graphic::HeaderShaderConstantBuffer> header_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::CameraShaderStructuredBuffer> camera_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::LightShaderStructuredBuffer> light_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::FogShaderStructuredBuffer> fog_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Texture> main_render_target_texture;
	tml::shared_ptr<tml::graphic::Texture> main_depth_target_texture;
	tml::shared_ptr<tml::graphic::Sampler> cc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> cw_sampler;
	tml::shared_ptr<tml::graphic::Sampler> wc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> ww_sampler;

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
