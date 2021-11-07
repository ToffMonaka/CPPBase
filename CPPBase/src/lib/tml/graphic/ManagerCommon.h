/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../memory/MemoryUtil.h"


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
	tml::shared_ptr<tml::graphic::Texture> main_render_target_texture;
	tml::shared_ptr<tml::graphic::Texture> main_depth_target_texture;
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
	tml::shared_ptr<tml::graphic::Shader> figure_model_2d_shader;
	tml::shared_ptr<tml::graphic::Shader> ground_model_2d_shader;
	tml::shared_ptr<tml::graphic::Shader> figure_model_3d_shader;
	tml::shared_ptr<tml::graphic::Shader> ground_model_3d_shader;
	tml::shared_ptr<tml::graphic::ConfigShaderConstantBuffer> config_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::HeaderShaderConstantBuffer> header_shader_constant_buffer;
	tml::shared_ptr<tml::graphic::Camera2DShaderStructuredBuffer> camera_2d_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Camera3DShaderStructuredBuffer> camera_3d_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Light2DShaderStructuredBuffer> light_2d_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Light3DShaderStructuredBuffer> light_3d_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Fog2DShaderStructuredBuffer> fog_2d_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Fog3DShaderStructuredBuffer> fog_3d_shader_structured_buffer;
	tml::shared_ptr<tml::graphic::Mesh> figure_model_2d_mesh;
	tml::shared_ptr<tml::graphic::Mesh> figure_model_3d_mesh;
	tml::shared_ptr<tml::graphic::Sampler> cc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> cw_sampler;
	tml::shared_ptr<tml::graphic::Sampler> wc_sampler;
	tml::shared_ptr<tml::graphic::Sampler> ww_sampler;

private:
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
 * @brief Release関数
 */
inline void tml::graphic::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
