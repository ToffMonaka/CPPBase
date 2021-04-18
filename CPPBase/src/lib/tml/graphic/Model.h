/**
 * @file
 * @brief Model�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelLayer�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
 * @brief Release�֐�
 */
inline void tml::graphic::ModelLayer::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ModelLayer::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetMeshIndex�֐�
 * @return mesh_index (mesh_index)
 */
inline UINT tml::graphic::ModelLayer::GetMeshIndex(void) const
{
	return (this->mesh_index_);
}


/**
 * @brief SetMeshIndex�֐�
 * @param mesh_index (mesh_index)
 */
inline void tml::graphic::ModelLayer::SetMeshIndex(const UINT mesh_index)
{
	this->mesh_index_ = mesh_index;

	return;
}


/**
 * @brief GetDiffuseTextureIndex�֐�
 * @return diffuse_tex_index (diffuse_texture_index)
 */
inline UINT tml::graphic::ModelLayer::GetDiffuseTextureIndex(void) const
{
	return (this->diffuse_tex_index_);
}


/**
 * @brief SetDiffuseTextureIndex�֐�
 * @param diffuse_tex_index (diffuse_texture_index)
 */
inline void tml::graphic::ModelLayer::SetDiffuseTextureIndex(const UINT diffuse_tex_index)
{
	this->diffuse_tex_index_ = diffuse_tex_index;

	return;
}


/**
 * @brief GetDiffuseSamplerIndex�֐�
 * @return diffuse_samp_index (diffuse_sampler_index)
 */
inline UINT tml::graphic::ModelLayer::GetDiffuseSamplerIndex(void) const
{
	return (this->diffuse_samp_index_);
}


/**
 * @brief SetDiffuseSamplerIndex�֐�
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
 * @brief ModelStage�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
	tml::graphic::ModelLayer *GetLayer(const UINT);
	tml::graphic::ModelLayer *GetLayerFast(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::ModelLayer> &);
};
}
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ModelStage::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetRasterizerStateIndex�֐�
 * @return rs_index (rasterizer_state_index)
 */
inline UINT tml::graphic::ModelStage::GetRasterizerStateIndex(void) const
{
	return (this->rs_index_);
}


/**
 * @brief SetRasterizerStateIndex�֐�
 * @param rs_index (rasterizer_state_index)
 */
inline void tml::graphic::ModelStage::SetRasterizerStateIndex(const UINT rs_index)
{
	this->rs_index_ = rs_index;

	return;
}


/**
 * @brief GetBlendStateIndex�֐�
 * @return bs_index (blend_state_index)
 */
inline UINT tml::graphic::ModelStage::GetBlendStateIndex(void) const
{
	return (this->bs_index_);
}


/**
 * @brief SetBlendStateIndex�֐�
 * @param bs_index (blend_state_index)
 */
inline void tml::graphic::ModelStage::SetBlendStateIndex(const UINT bs_index)
{
	this->bs_index_ = bs_index;

	return;
}


/**
 * @brief GetDepthStateIndex�֐�
 * @return ds_index (depth_state_index)
 */
inline UINT tml::graphic::ModelStage::GetDepthStateIndex(void) const
{
	return (this->ds_index_);
}


/**
 * @brief SetDepthStateIndex�֐�
 * @param ds_index (depth_state_index)
 */
inline void tml::graphic::ModelStage::SetDepthStateIndex(const UINT ds_index)
{
	this->ds_index_ = ds_index;

	return;
}


/**
 * @brief GetShaderIndex�֐�
 * @return shader_index (shader_state_index)
 */
inline UINT tml::graphic::ModelStage::GetShaderIndex(void) const
{
	return (this->shader_index_);
}


/**
 * @brief SetShaderIndex�֐�
 * @param shader_index (shader_index)
 */
inline void tml::graphic::ModelStage::SetShaderIndex(const UINT shader_index)
{
	this->shader_index_ = shader_index;

	return;
}


/**
 * @brief GetLayerCount�֐�
 * @return layer_cnt (layer_count)
 */
inline UINT tml::graphic::ModelStage::GetLayerCount(void) const
{
	return (this->layer_cont_.size());
}


/**
 * @brief GetLayer�֐�
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=���s
 */
inline tml::graphic::ModelLayer *tml::graphic::ModelStage::GetLayer(const UINT index)
{
	if (index >= this->layer_cont_.size()) {
		return (nullptr);
	}

	return (this->layer_cont_[index].get());
}


/**
 * @brief GetLayerFast�֐�
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=���s
 */
inline tml::graphic::ModelLayer *tml::graphic::ModelStage::GetLayerFast(const UINT index)
{
	return (this->layer_cont_[index].get());
}


namespace tml {
namespace graphic {
/**
 * @brief ModelDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::graphic::ModelDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Model : public tml::graphic::ManagerResource
{
public: Model(const tml::graphic::Model &) = delete;
public: tml::graphic::Model &operator =(const tml::graphic::Model &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::MODEL_TYPE type_;
	std::vector<tml::shared_ptr<tml::graphic::RasterizerState>> rs_cont_;
	std::vector<tml::shared_ptr<tml::graphic::BlendState>> bs_cont_;
	std::vector<tml::shared_ptr<tml::graphic::DepthState>> ds_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Shader>> shader_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Mesh>> mesh_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Texture>> tex_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Sampler>> samp_cont_;

	std::array<tml::unique_ptr<tml::graphic::ModelStage>, tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE_COUNT> stage_cont_;

public:

protected:
	void Release(void);
	INT Create(const tml::graphic::ModelDesc &, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::MODEL_TYPE GetType(void) const;
	UINT GetRasterizerStateCount(void) const;
	tml::graphic::RasterizerState *GetRasterizerState(const UINT);
	tml::graphic::RasterizerState *GetRasterizerStateFast(const UINT);
	void SetRasterizerState(const UINT, tml::shared_ptr<tml::graphic::RasterizerState> &);
	UINT GetBlendStateCount(void) const;
	tml::graphic::BlendState *GetBlendState(const UINT);
	tml::graphic::BlendState *GetBlendStateFast(const UINT);
	void SetBlendState(const UINT, tml::shared_ptr<tml::graphic::BlendState> &);
	UINT GetDepthStateCount(void) const;
	tml::graphic::DepthState *GetDepthState(const UINT);
	tml::graphic::DepthState *GetDepthStateFast(const UINT);
	void SetDepthState(const UINT, tml::shared_ptr<tml::graphic::DepthState> &);
	UINT GetShaderCount(void) const;
	tml::graphic::Shader *GetShader(const UINT);
	tml::graphic::Shader *GetShaderFast(const UINT);
	void SetShader(const UINT, tml::shared_ptr<tml::graphic::Shader> &);
	UINT GetMeshCount(void) const;
	tml::graphic::Mesh *GetMesh(const UINT);
	tml::graphic::Mesh *GetMeshFast(const UINT);
	void SetMesh(const UINT, tml::shared_ptr<tml::graphic::Mesh> &);
	UINT GetTextureCount(void) const;
	tml::graphic::Texture *GetTexture(const UINT);
	tml::graphic::Texture *GetTextureFast(const UINT);
	void SetTexture(const UINT, tml::shared_ptr<tml::graphic::Texture> &);
	UINT GetSamplerCount(void) const;
	tml::graphic::Sampler *GetSampler(const UINT);
	tml::graphic::Sampler *GetSamplerFast(const UINT);
	void SetSampler(const UINT, tml::shared_ptr<tml::graphic::Sampler> &);

	UINT GetStageCount(void) const;
	tml::graphic::ModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::ModelStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::ModelStage> &);

	virtual void DrawStageInit(void);
	virtual void DrawStageDeferred3D(void);
	virtual void DrawStageDeferredShadow3D(void);
	virtual void DrawStageForward3D(void);
	virtual void DrawStageForward2D(void);
};
}
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::MODEL_TYPE tml::graphic::Model::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRasterizerStateCount�֐�
 * @return rs_cnt (rasterizer_state_count)
 */
inline UINT tml::graphic::Model::GetRasterizerStateCount(void) const
{
	return (this->rs_cont_.size());
}


/**
 * @brief GetRasterizerState�֐�
 * @param index (index)
 * @return rs (rasterizer_state)<br>
 * nullptr=���s
 */
inline tml::graphic::RasterizerState *tml::graphic::Model::GetRasterizerState(const UINT index)
{
	if (index >= this->rs_cont_.size()) {
		return (nullptr);
	}

	return (this->rs_cont_[index].get());
}


/**
 * @brief GetRasterizerStateFast�֐�
 * @param index (index)
 * @return rs (rasterizer_state)<br>
 * nullptr=���s
 */
inline tml::graphic::RasterizerState *tml::graphic::Model::GetRasterizerStateFast(const UINT index)
{
	return (this->rs_cont_[index].get());
}


/**
 * @brief GetBlendStateCount�֐�
 * @return bs_cnt (blend_state_count)
 */
inline UINT tml::graphic::Model::GetBlendStateCount(void) const
{
	return (this->bs_cont_.size());
}


/**
 * @brief GetBlendState�֐�
 * @param index (index)
 * @return bs (blend_state)<br>
 * nullptr=���s
 */
inline tml::graphic::BlendState *tml::graphic::Model::GetBlendState(const UINT index)
{
	if (index >= this->bs_cont_.size()) {
		return (nullptr);
	}

	return (this->bs_cont_[index].get());
}


/**
 * @brief GetBlendStateFast�֐�
 * @param index (index)
 * @return bs (blend_state)<br>
 * nullptr=���s
 */
inline tml::graphic::BlendState *tml::graphic::Model::GetBlendStateFast(const UINT index)
{
	return (this->bs_cont_[index].get());
}


/**
 * @brief GetDepthStateCount�֐�
 * @return ds_cnt (depth_state_count)
 */
inline UINT tml::graphic::Model::GetDepthStateCount(void) const
{
	return (this->ds_cont_.size());
}


/**
 * @brief GetDepthState�֐�
 * @param index (index)
 * @return ds (depth_state)<br>
 * nullptr=���s
 */
inline tml::graphic::DepthState *tml::graphic::Model::GetDepthState(const UINT index)
{
	if (index >= this->ds_cont_.size()) {
		return (nullptr);
	}

	return (this->ds_cont_[index].get());
}


/**
 * @brief GetDepthStateFast�֐�
 * @param index (index)
 * @return ds (depth_state)<br>
 * nullptr=���s
 */
inline tml::graphic::DepthState *tml::graphic::Model::GetDepthStateFast(const UINT index)
{
	return (this->ds_cont_[index].get());
}


/**
 * @brief GetShaderCount�֐�
 * @return shader_cnt (shader_count)
 */
inline UINT tml::graphic::Model::GetShaderCount(void) const
{
	return (this->shader_cont_.size());
}


/**
 * @brief GetShader�֐�
 * @param index (index)
 * @return shader (shader)<br>
 * nullptr=���s
 */
inline tml::graphic::Shader *tml::graphic::Model::GetShader(const UINT index)
{
	if (index >= this->shader_cont_.size()) {
		return (nullptr);
	}

	return (this->shader_cont_[index].get());
}


/**
 * @brief GetShaderFast�֐�
 * @param index (index)
 * @return shader (shader)<br>
 * nullptr=���s
 */
inline tml::graphic::Shader *tml::graphic::Model::GetShaderFast(const UINT index)
{
	return (this->shader_cont_[index].get());
}


/**
 * @brief GetMeshCount�֐�
 * @return mesh_cnt (mesh_count)
 */
inline UINT tml::graphic::Model::GetMeshCount(void) const
{
	return (this->mesh_cont_.size());
}


/**
 * @brief GetMesh�֐�
 * @param index (index)
 * @return mesh (mesh)<br>
 * nullptr=���s
 */
inline tml::graphic::Mesh *tml::graphic::Model::GetMesh(const UINT index)
{
	if (index >= this->mesh_cont_.size()) {
		return (nullptr);
	}

	return (this->mesh_cont_[index].get());
}


/**
 * @brief GetMeshFast�֐�
 * @param index (index)
 * @return mesh (mesh)<br>
 * nullptr=���s
 */
inline tml::graphic::Mesh *tml::graphic::Model::GetMeshFast(const UINT index)
{
	return (this->mesh_cont_[index].get());
}


/**
 * @brief GetTextureCount�֐�
 * @return tex_cnt (texture_count)
 */
inline UINT tml::graphic::Model::GetTextureCount(void) const
{
	return (this->tex_cont_.size());
}


/**
 * @brief GetTexture�֐�
 * @param index (index)
 * @return tex (texture)<br>
 * nullptr=���s
 */
inline tml::graphic::Texture *tml::graphic::Model::GetTexture(const UINT index)
{
	if (index >= this->tex_cont_.size()) {
		return (nullptr);
	}

	return (this->tex_cont_[index].get());
}


/**
 * @brief GetTextureFast�֐�
 * @param index (index)
 * @return tex (texture)<br>
 * nullptr=���s
 */
inline tml::graphic::Texture *tml::graphic::Model::GetTextureFast(const UINT index)
{
	return (this->tex_cont_[index].get());
}


/**
 * @brief GetSamplerCount�֐�
 * @return samp_cnt (sampler_count)
 */
inline UINT tml::graphic::Model::GetSamplerCount(void) const
{
	return (this->samp_cont_.size());
}


/**
 * @brief GetSampler�֐�
 * @param index (index)
 * @return samp (sampler)<br>
 * nullptr=���s
 */
inline tml::graphic::Sampler *tml::graphic::Model::GetSampler(const UINT index)
{
	if (index >= this->samp_cont_.size()) {
		return (nullptr);
	}

	return (this->samp_cont_[index].get());
}


/**
 * @brief GetSamplerFast�֐�
 * @param index (index)
 * @return samp (sampler)<br>
 * nullptr=���s
 */
inline tml::graphic::Sampler *tml::graphic::Model::GetSamplerFast(const UINT index)
{
	return (this->samp_cont_[index].get());
}


/**
 * @brief GetStageCount�֐�
 * @return stage_cnt (stage_count)
 */
inline UINT tml::graphic::Model::GetStageCount(void) const
{
	return (this->stage_cont_.size());
}


/**
 * @brief GetStage�֐�
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=���s
 */
inline tml::graphic::ModelStage *tml::graphic::Model::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (this->stage_cont_[static_cast<UINT>(type)].get());
}


/**
 * @brief GetStageFast�֐�
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=���s
 */
inline tml::graphic::ModelStage *tml::graphic::Model::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (this->stage_cont_[static_cast<UINT>(type)].get());
}


#if 0
namespace tml {
namespace graphic {
/**
 * @brief MaterialDesc�N���X
 */
class MaterialDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::XMFLOAT3EX diffuse_color;
	FLOAT diffuse_mul_value;
	FLOAT transparent_mul_value;
	FLOAT burn_mul_value;
	FLOAT emissive_mul_value;
	FLOAT bloom_mul_value;
	FLOAT specular_mul_value;
	FLOAT specular_exp_value;
	FLOAT rim_mul_value;
	FLOAT rim_exp_value;
	bool light_flag;
	bool fog_flag;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	MaterialDesc();
	virtual ~MaterialDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::MaterialDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Material�N���X
 */
class Material : public tml::graphic::ManagerResource
{
public: Material(const tml::graphic::Material &) = delete;
public: tml::graphic::Material &operator =(const tml::graphic::Material &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::XMFLOAT3EX diffuse_col_;
	FLOAT diffuse_mul_val_;
	FLOAT transparent_mul_val_;
	FLOAT burn_mul_val_;
	FLOAT emissive_mul_val_;
	FLOAT bloom_mul_val_;
	FLOAT specular_mul_val_;
	FLOAT specular_exp_val_;
	FLOAT rim_mul_val_;
	FLOAT rim_exp_val_;
	bool light_flg_;
	bool fog_flg_;

protected:
	void Release(void);

public:
	Material();
	virtual ~Material();

	virtual void Init(void);
	INT Create(const tml::graphic::MaterialDesc &);

	const tml::XMFLOAT3EX &GetDiffuseColor(void) const;
	void SetDiffuseColor(const tml::XMFLOAT3EX &);
	FLOAT GetDiffuseMulValue(void) const;
	void SetDiffuseMulValue(const FLOAT);
	FLOAT GetTransparentMulValue(void) const;
	void SetTransparentMulValue(const FLOAT);
	FLOAT GetBurnMulValue(void) const;
	void SetBurnMulValue(const FLOAT);
	FLOAT GetEmissiveMulValue(void) const;
	void SetEmissiveMulValue(const FLOAT);
	FLOAT GetBloomMulValue(void) const;
	void SetBloomMulValue(const FLOAT);
	FLOAT GetSpecularMulValue(void) const;
	void SetSpecularMulValue(const FLOAT);
	FLOAT GetSpecularExpValue(void) const;
	void SetSpecularExpValue(const FLOAT);
	FLOAT GetRimMulValue(void) const;
	void SetRimMulValue(const FLOAT);
	FLOAT GetRimExpValue(void) const;
	void SetRimExpValue(const FLOAT);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Material::Release(void)
{
	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief GetDiffuseColor�֐�
 * @return diffuse_col (diffuse_color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Material::GetDiffuseColor(void) const
{
	return (this->diffuse_col_);
}


/**
 * @brief SetDiffuseColor�֐�
 * @param diffuse_col (diffuse_color)
 */
inline void tml::graphic::Material::SetDiffuseColor(const tml::XMFLOAT3EX &diffuse_col)
{
	this->diffuse_col_ = diffuse_col;

	return;
}


/**
 * @brief GetDiffuseMulValue�֐�
 * @return diffuse_mul_val (diffuse_mul_value)
 */
inline FLOAT tml::graphic::Material::GetDiffuseMulValue(void) const
{
	return (this->diffuse_mul_val_);
}


/**
 * @brief SetDiffuseMulValue�֐�
 * @param diffuse_mul_val (diffuse_mul_value)
 */
inline void tml::graphic::Material::SetDiffuseMulValue(const FLOAT diffuse_mul_val)
{
	this->diffuse_mul_val_ = diffuse_mul_val;
	
	return;
}


/**
 * @brief GetTransparentMulValue�֐�
 * @return transparent_mul_val (transparent_mul_value)
 */
inline FLOAT tml::graphic::Material::GetTransparentMulValue(void) const
{
	return (this->transparent_mul_val_);
}


/**
 * @brief SetTransparentMulValue�֐�
 * @param transparent_mul_val (transparent_mul_value)
 */
inline void tml::graphic::Material::SetTransparentMulValue(const FLOAT transparent_mul_val)
{
	this->transparent_mul_val_ = transparent_mul_val;
	
	return;
}


/**
 * @brief GetBurnMulValue�֐�
 * @return burn_mul_val (burn_mul_value)
 */
inline FLOAT tml::graphic::Material::GetBurnMulValue(void) const
{
	return (this->burn_mul_val_);
}


/**
 * @brief SetBurnMulValue�֐�
 * @param burn_mul_val (burn_mul_value)
 */
inline void tml::graphic::Material::SetBurnMulValue(const FLOAT burn_mul_val)
{
	this->burn_mul_val_ = burn_mul_val;
	
	return;
}


/**
 * @brief GetEmissiveMulValue�֐�
 * @return emissive_mul_val (emissive_mul_value)
 */
inline FLOAT tml::graphic::Material::GetEmissiveMulValue(void) const
{
	return (this->emissive_mul_val_);
}


/**
 * @brief SetEmissiveMulValue�֐�
 * @param emissive_mul_val (emissive_mul_value)
 */
inline void tml::graphic::Material::SetEmissiveMulValue(const FLOAT emissive_mul_val)
{
	this->emissive_mul_val_ = emissive_mul_val;
	
	return;
}


/**
 * @brief GetBloomMulValue�֐�
 * @return bloom_mul_val (bloom_mul_value)
 */
inline FLOAT tml::graphic::Material::GetBloomMulValue(void) const
{
	return (this->bloom_mul_val_);
}


/**
 * @brief SetBloomMulValue�֐�
 * @param bloom_mul_val (bloom_mul_value)
 */
inline void tml::graphic::Material::SetBloomMulValue(const FLOAT bloom_mul_val)
{
	this->bloom_mul_val_ = bloom_mul_val;
	
	return;
}


/**
 * @brief GetSpecularMulValue�֐�
 * @return specular_mul_val (specular_mul_value)
 */
inline FLOAT tml::graphic::Material::GetSpecularMulValue(void) const
{
	return (this->specular_mul_val_);
}


/**
 * @brief SetSpecularMulValue�֐�
 * @param specular_mul_val (specular_mul_value)
 */
inline void tml::graphic::Material::SetSpecularMulValue(const FLOAT specular_mul_val)
{
	this->specular_mul_val_ = specular_mul_val;
	
	return;
}


/**
 * @brief GetSpecularExpValue�֐�
 * @return specular_exp_val (specular_exp_value)
 */
inline FLOAT tml::graphic::Material::GetSpecularExpValue(void) const
{
	return (this->specular_exp_val_);
}


/**
 * @brief SetSpecularExpValue�֐�
 * @param specular_exp_val (specular_exp_value)
 */
inline void tml::graphic::Material::SetSpecularExpValue(const FLOAT specular_exp_val)
{
	this->specular_exp_val_ = specular_exp_val;
	
	return;
}


/**
 * @brief GetRimMulValue�֐�
 * @return rim_mul_val (rim_mul_value)
 */
inline FLOAT tml::graphic::Material::GetRimMulValue(void) const
{
	return (this->rim_mul_val_);
}


/**
 * @brief SetRimMulValue�֐�
 * @param rim_mul_val (rim_mul_value)
 */
inline void tml::graphic::Material::SetRimMulValue(const FLOAT rim_mul_val)
{
	this->rim_mul_val_ = rim_mul_val;
	
	return;
}


/**
 * @brief GetRimExpValue�֐�
 * @return rim_exp_val (rim_exp_value)
 */
inline FLOAT tml::graphic::Material::GetRimExpValue(void) const
{
	return (this->rim_exp_val_);
}


/**
 * @brief SetRimExpValue�֐�
 * @param rim_exp_val (rim_exp_value)
 */
inline void tml::graphic::Material::SetRimExpValue(const FLOAT rim_exp_val)
{
	this->rim_exp_val_ = rim_exp_val;
	
	return;
}
#endif
