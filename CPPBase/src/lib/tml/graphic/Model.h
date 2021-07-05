/**
 * @file
 * @brief Modelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathINT.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelLayerクラス
 *
 * インターフェースパターン
 */
class ModelLayer
{
public: ModelLayer(const tml::graphic::ModelLayer &) = delete;
public: tml::graphic::ModelLayer &operator =(const tml::graphic::ModelLayer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;
	UINT mesh_index_;
	UINT diffuse_tex_index_;
	UINT diffuse_samp_index_;

protected:
	void Release(void);
	INT Create(tml::graphic::Manager *);

public:
	ModelLayer();
	virtual ~ModelLayer();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void);
	UINT GetMeshIndex(void) const;
	void SetMeshIndex(const UINT);
	UINT GetDiffuseTextureIndex(void) const;
	void SetDiffuseTextureIndex(const UINT);
	UINT GetDiffuseSamplerIndex(void) const;
	void SetDiffuseSamplerIndex(const UINT);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ModelLayer::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetMeshIndex関数
 * @return mesh_index (mesh_index)
 */
inline UINT tml::graphic::ModelLayer::GetMeshIndex(void) const
{
	return (this->mesh_index_);
}


/**
 * @brief SetMeshIndex関数
 * @param mesh_index (mesh_index)
 */
inline void tml::graphic::ModelLayer::SetMeshIndex(const UINT mesh_index)
{
	this->mesh_index_ = mesh_index;

	return;
}


/**
 * @brief GetDiffuseTextureIndex関数
 * @return diffuse_tex_index (diffuse_texture_index)
 */
inline UINT tml::graphic::ModelLayer::GetDiffuseTextureIndex(void) const
{
	return (this->diffuse_tex_index_);
}


/**
 * @brief SetDiffuseTextureIndex関数
 * @param diffuse_tex_index (diffuse_texture_index)
 */
inline void tml::graphic::ModelLayer::SetDiffuseTextureIndex(const UINT diffuse_tex_index)
{
	this->diffuse_tex_index_ = diffuse_tex_index;

	return;
}


/**
 * @brief GetDiffuseSamplerIndex関数
 * @return diffuse_samp_index (diffuse_sampler_index)
 */
inline UINT tml::graphic::ModelLayer::GetDiffuseSamplerIndex(void) const
{
	return (this->diffuse_samp_index_);
}


/**
 * @brief SetDiffuseSamplerIndex関数
 * @param diffuse_samp_index (diffuse_sampler_index)
 */
inline void tml::graphic::ModelLayer::SetDiffuseSamplerIndex(const UINT diffuse_samp_index)
{
	this->diffuse_samp_index_ = diffuse_samp_index;

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ModelStageクラス
 *
 * インターフェースパターン
 */
class ModelStage
{
public: ModelStage(const tml::graphic::ModelStage &) = delete;
public: tml::graphic::ModelStage &operator =(const tml::graphic::ModelStage &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;
	UINT rs_index_;
	UINT bs_index_;
	UINT ds_index_;
	UINT shader_index_;

	std::vector<tml::unique_ptr<tml::graphic::ModelLayer>> layer_cont_;

protected:
	void Release(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::ModelLayer *GetLayer(const UINT);
	tml::graphic::ModelLayer *GetLayerFast(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::ModelLayer> &);

public:
	ModelStage();
	virtual ~ModelStage();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void);
	UINT GetRasterizerStateIndex(void) const;
	void SetRasterizerStateIndex(const UINT);
	UINT GetBlendStateIndex(void) const;
	void SetBlendStateIndex(const UINT);
	UINT GetDepthStateIndex(void) const;
	void SetDepthStateIndex(const UINT);
	UINT GetShaderIndex(void) const;
	void SetShaderIndex(const UINT);

	UINT GetLayerCount(void) const;
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ModelStage::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetRasterizerStateIndex関数
 * @return rs_index (rasterizer_state_index)
 */
inline UINT tml::graphic::ModelStage::GetRasterizerStateIndex(void) const
{
	return (this->rs_index_);
}


/**
 * @brief SetRasterizerStateIndex関数
 * @param rs_index (rasterizer_state_index)
 */
inline void tml::graphic::ModelStage::SetRasterizerStateIndex(const UINT rs_index)
{
	this->rs_index_ = rs_index;

	return;
}


/**
 * @brief GetBlendStateIndex関数
 * @return bs_index (blend_state_index)
 */
inline UINT tml::graphic::ModelStage::GetBlendStateIndex(void) const
{
	return (this->bs_index_);
}


/**
 * @brief SetBlendStateIndex関数
 * @param bs_index (blend_state_index)
 */
inline void tml::graphic::ModelStage::SetBlendStateIndex(const UINT bs_index)
{
	this->bs_index_ = bs_index;

	return;
}


/**
 * @brief GetDepthStateIndex関数
 * @return ds_index (depth_state_index)
 */
inline UINT tml::graphic::ModelStage::GetDepthStateIndex(void) const
{
	return (this->ds_index_);
}


/**
 * @brief SetDepthStateIndex関数
 * @param ds_index (depth_state_index)
 */
inline void tml::graphic::ModelStage::SetDepthStateIndex(const UINT ds_index)
{
	this->ds_index_ = ds_index;

	return;
}


/**
 * @brief GetShaderIndex関数
 * @return shader_index (shader_state_index)
 */
inline UINT tml::graphic::ModelStage::GetShaderIndex(void) const
{
	return (this->shader_index_);
}


/**
 * @brief SetShaderIndex関数
 * @param shader_index (shader_index)
 */
inline void tml::graphic::ModelStage::SetShaderIndex(const UINT shader_index)
{
	this->shader_index_ = shader_index;

	return;
}


/**
 * @brief GetLayerCount関数
 * @return layer_cnt (layer_count)
 */
inline UINT tml::graphic::ModelStage::GetLayerCount(void) const
{
	return (this->layer_cont_.size());
}


/**
 * @brief GetLayer関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::ModelLayer *tml::graphic::ModelStage::GetLayer(const UINT index)
{
	if (index >= this->layer_cont_.size()) {
		return (nullptr);
	}

	return (this->layer_cont_[index].get());
}


/**
 * @brief GetLayerFast関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::ModelLayer *tml::graphic::ModelStage::GetLayerFast(const UINT index)
{
	return (this->layer_cont_[index].get());
}


namespace tml {
namespace graphic {
/**
 * @brief ModelDescクラス
 */
class ModelDesc : public tml::graphic::ManagerResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ModelDesc();
	virtual ~ModelDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ModelDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Modelクラス
 *
 * インターフェースパターン
 */
class Model : public tml::graphic::ManagerResource
{
public: Model(const tml::graphic::Model &) = delete;
public: tml::graphic::Model &operator =(const tml::graphic::Model &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::MODEL_TYPE type_;
	std::vector<tml::shared_ptr<tml::graphic::RasterizerState>> rs_cont_;
	tml::shared_ptr<tml::graphic::RasterizerState> empty_rs_;
	std::vector<tml::shared_ptr<tml::graphic::BlendState>> bs_cont_;
	tml::shared_ptr<tml::graphic::BlendState> empty_bs_;
	std::vector<tml::shared_ptr<tml::graphic::DepthState>> ds_cont_;
	tml::shared_ptr<tml::graphic::DepthState> empty_ds_;
	std::vector<tml::shared_ptr<tml::graphic::Shader>> shader_cont_;
	tml::shared_ptr<tml::graphic::Shader> empty_shader_;
	std::vector<tml::shared_ptr<tml::graphic::Mesh>> mesh_cont_;
	tml::shared_ptr<tml::graphic::Mesh> empty_mesh_;
	std::vector<tml::shared_ptr<tml::graphic::Texture>> tex_cont_;
	tml::shared_ptr<tml::graphic::Texture> empty_tex_;
	std::vector<tml::shared_ptr<tml::graphic::Sampler>> samp_cont_;
	tml::shared_ptr<tml::graphic::Sampler> empty_samp_;

	std::array<tml::unique_ptr<tml::graphic::ModelStage>, tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE_COUNT> stage_cont_;

protected:
	void Release(void);
	INT Create(const tml::graphic::ModelDesc &, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE);

	tml::graphic::ModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::ModelStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::ModelStage> &);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::MODEL_TYPE GetType(void) const;
	UINT GetRasterizerStateCount(void) const;
	const tml::shared_ptr<tml::graphic::RasterizerState> &GetRasterizerState(const UINT);
	const tml::shared_ptr<tml::graphic::RasterizerState> &GetRasterizerStateFast(const UINT);
	void SetRasterizerState(const UINT, const tml::shared_ptr<tml::graphic::RasterizerState> &);
	UINT GetBlendStateCount(void) const;
	const tml::shared_ptr<tml::graphic::BlendState> &GetBlendState(const UINT);
	const tml::shared_ptr<tml::graphic::BlendState> &GetBlendStateFast(const UINT);
	void SetBlendState(const UINT, const tml::shared_ptr<tml::graphic::BlendState> &);
	UINT GetDepthStateCount(void) const;
	const tml::shared_ptr<tml::graphic::DepthState> &GetDepthState(const UINT);
	const tml::shared_ptr<tml::graphic::DepthState> &GetDepthStateFast(const UINT);
	void SetDepthState(const UINT, const tml::shared_ptr<tml::graphic::DepthState> &);
	UINT GetShaderCount(void) const;
	const tml::shared_ptr<tml::graphic::Shader> &GetShader(const UINT);
	const tml::shared_ptr<tml::graphic::Shader> &GetShaderFast(const UINT);
	void SetShader(const UINT, const tml::shared_ptr<tml::graphic::Shader> &);
	UINT GetMeshCount(void) const;
	const tml::shared_ptr<tml::graphic::Mesh> &GetMesh(const UINT);
	const tml::shared_ptr<tml::graphic::Mesh> &GetMeshFast(const UINT);
	void SetMesh(const UINT, const tml::shared_ptr<tml::graphic::Mesh> &);
	UINT GetTextureCount(void) const;
	const tml::shared_ptr<tml::graphic::Texture> &GetTexture(const UINT);
	const tml::shared_ptr<tml::graphic::Texture> &GetTextureFast(const UINT);
	void SetTexture(const UINT, const tml::shared_ptr<tml::graphic::Texture> &);
	UINT GetSamplerCount(void) const;
	const tml::shared_ptr<tml::graphic::Sampler> &GetSampler(const UINT);
	const tml::shared_ptr<tml::graphic::Sampler> &GetSamplerFast(const UINT);
	void SetSampler(const UINT, const tml::shared_ptr<tml::graphic::Sampler> &);

	UINT GetStageCount(void) const;

	virtual bool IsHitByMouseDevice(const tml::XMINT2EX &);
	virtual void DrawStageInit(void);
	virtual void DrawStageDeferred3D(void);
	virtual void DrawStageDeferredShadow3D(void);
	virtual void DrawStageForward3D(void);
	virtual void DrawStageForward2D(void);
};
}
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::MODEL_TYPE tml::graphic::Model::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRasterizerStateCount関数
 * @return rs_cnt (rasterizer_state_count)
 */
inline UINT tml::graphic::Model::GetRasterizerStateCount(void) const
{
	return (this->rs_cont_.size());
}


/**
 * @brief GetRasterizerState関数
 * @param index (index)
 * @return rs (rasterizer_state)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::RasterizerState> &tml::graphic::Model::GetRasterizerState(const UINT index)
{
	if (index >= this->rs_cont_.size()) {
		return (this->empty_rs_);
	}

	return (this->rs_cont_[index]);
}


/**
 * @brief GetRasterizerStateFast関数
 * @param index (index)
 * @return rs (rasterizer_state)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::RasterizerState> &tml::graphic::Model::GetRasterizerStateFast(const UINT index)
{
	return (this->rs_cont_[index]);
}


/**
 * @brief GetBlendStateCount関数
 * @return bs_cnt (blend_state_count)
 */
inline UINT tml::graphic::Model::GetBlendStateCount(void) const
{
	return (this->bs_cont_.size());
}


/**
 * @brief GetBlendState関数
 * @param index (index)
 * @return bs (blend_state)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::BlendState> &tml::graphic::Model::GetBlendState(const UINT index)
{
	if (index >= this->bs_cont_.size()) {
		return (this->empty_bs_);
	}

	return (this->bs_cont_[index]);
}


/**
 * @brief GetBlendStateFast関数
 * @param index (index)
 * @return bs (blend_state)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::BlendState> &tml::graphic::Model::GetBlendStateFast(const UINT index)
{
	return (this->bs_cont_[index]);
}


/**
 * @brief GetDepthStateCount関数
 * @return ds_cnt (depth_state_count)
 */
inline UINT tml::graphic::Model::GetDepthStateCount(void) const
{
	return (this->ds_cont_.size());
}


/**
 * @brief GetDepthState関数
 * @param index (index)
 * @return ds (depth_state)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::DepthState> &tml::graphic::Model::GetDepthState(const UINT index)
{
	if (index >= this->ds_cont_.size()) {
		return (this->empty_ds_);
	}

	return (this->ds_cont_[index]);
}


/**
 * @brief GetDepthStateFast関数
 * @param index (index)
 * @return ds (depth_state)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::DepthState> &tml::graphic::Model::GetDepthStateFast(const UINT index)
{
	return (this->ds_cont_[index]);
}


/**
 * @brief GetShaderCount関数
 * @return shader_cnt (shader_count)
 */
inline UINT tml::graphic::Model::GetShaderCount(void) const
{
	return (this->shader_cont_.size());
}


/**
 * @brief GetShader関数
 * @param index (index)
 * @return shader (shader)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Shader> &tml::graphic::Model::GetShader(const UINT index)
{
	if (index >= this->shader_cont_.size()) {
		return (this->empty_shader_);
	}

	return (this->shader_cont_[index]);
}


/**
 * @brief GetShaderFast関数
 * @param index (index)
 * @return shader (shader)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Shader> &tml::graphic::Model::GetShaderFast(const UINT index)
{
	return (this->shader_cont_[index]);
}


/**
 * @brief GetMeshCount関数
 * @return mesh_cnt (mesh_count)
 */
inline UINT tml::graphic::Model::GetMeshCount(void) const
{
	return (this->mesh_cont_.size());
}


/**
 * @brief GetMesh関数
 * @param index (index)
 * @return mesh (mesh)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Mesh> &tml::graphic::Model::GetMesh(const UINT index)
{
	if (index >= this->mesh_cont_.size()) {
		return (this->empty_mesh_);
	}

	return (this->mesh_cont_[index]);
}


/**
 * @brief GetMeshFast関数
 * @param index (index)
 * @return mesh (mesh)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Mesh> &tml::graphic::Model::GetMeshFast(const UINT index)
{
	return (this->mesh_cont_[index]);
}


/**
 * @brief GetTextureCount関数
 * @return tex_cnt (texture_count)
 */
inline UINT tml::graphic::Model::GetTextureCount(void) const
{
	return (this->tex_cont_.size());
}


/**
 * @brief GetTexture関数
 * @param index (index)
 * @return tex (texture)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Model::GetTexture(const UINT index)
{
	if (index >= this->tex_cont_.size()) {
		return (this->empty_tex_);
	}

	return (this->tex_cont_[index]);
}


/**
 * @brief GetTextureFast関数
 * @param index (index)
 * @return tex (texture)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Model::GetTextureFast(const UINT index)
{
	return (this->tex_cont_[index]);
}


/**
 * @brief GetSamplerCount関数
 * @return samp_cnt (sampler_count)
 */
inline UINT tml::graphic::Model::GetSamplerCount(void) const
{
	return (this->samp_cont_.size());
}


/**
 * @brief GetSampler関数
 * @param index (index)
 * @return samp (sampler)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Sampler> &tml::graphic::Model::GetSampler(const UINT index)
{
	if (index >= this->samp_cont_.size()) {
		return (this->empty_samp_);
	}

	return (this->samp_cont_[index]);
}


/**
 * @brief GetSamplerFast関数
 * @param index (index)
 * @return samp (sampler)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Sampler> &tml::graphic::Model::GetSamplerFast(const UINT index)
{
	return (this->samp_cont_[index]);
}


/**
 * @brief GetStageCount関数
 * @return stage_cnt (stage_count)
 */
inline UINT tml::graphic::Model::GetStageCount(void) const
{
	return (this->stage_cont_.size());
}


/**
 * @brief GetStage関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::ModelStage *tml::graphic::Model::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (this->stage_cont_[static_cast<UINT>(type)].get());
}


/**
 * @brief GetStageFast関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::ModelStage *tml::graphic::Model::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (this->stage_cont_[static_cast<UINT>(type)].get());
}
