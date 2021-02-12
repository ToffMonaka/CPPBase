/**
 * @file
 * @brief Modelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "Resource.h"


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
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ModelLayer::Release(void)
{
	return;
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
	tml::graphic::ModelLayer *GetLayer(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::ModelLayer> &);
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
 * @param ds_index (depth_state_index)
 */
inline void tml::graphic::ModelStage::SetShaderIndex(const UINT shader_index)
{
	this->shader_index_ = shader_index;

	return;
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


namespace tml {
namespace graphic {
/**
 * @brief ModelDescクラス
 */
class ModelDesc : public tml::graphic::ResourceDesc
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
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Modelクラス
 *
 * インターフェースパターン
 */
class Model : public tml::graphic::Resource
{
public: Model(const tml::graphic::Model &) = delete;
public: tml::graphic::Model &operator =(const tml::graphic::Model &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::MODEL_TYPE type_;
	std::vector<tml::unique_ptr<tml::graphic::ModelStage>> stage_cont_;
	std::vector<tml::shared_ptr<tml::graphic::RasterizerState>> rs_cont_;
	std::vector<tml::shared_ptr<tml::graphic::BlendState>> bs_cont_;
	std::vector<tml::shared_ptr<tml::graphic::DepthState>> ds_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Shader>> shader_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Mesh>> mesh_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Material>> material_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Texture>> tex_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Sampler>> samp_cont_;

public:

protected:
	void Release(void);
	INT Create(const tml::graphic::ModelDesc &, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::MODEL_TYPE GetType(void) const;
	tml::graphic::ModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::ModelStage> &);
	tml::graphic::RasterizerState *GetRasterizerState(const UINT);
	void SetRasterizerState(const UINT, tml::shared_ptr<tml::graphic::RasterizerState> &);
	tml::graphic::BlendState *GetBlendState(const UINT);
	void SetBlendState(const UINT, tml::shared_ptr<tml::graphic::BlendState> &);
	tml::graphic::DepthState *GetDepthState(const UINT);
	void SetDepthState(const UINT, tml::shared_ptr<tml::graphic::DepthState> &);
	tml::graphic::Shader *GetShader(const UINT);
	void SetShader(const UINT, tml::shared_ptr<tml::graphic::Shader> &);
	tml::graphic::Mesh *GetMesh(const UINT);
	void SetMesh(const UINT, tml::shared_ptr<tml::graphic::Mesh> &);
	tml::graphic::Material *GetMaterial(const UINT);
	void SetMaterial(const UINT, tml::shared_ptr<tml::graphic::Material> &);
	tml::graphic::Texture *GetTexture(const UINT);
	void SetTexture(const UINT, tml::shared_ptr<tml::graphic::Texture> &);
	tml::graphic::Sampler *GetSampler(const UINT);
	void SetSampler(const UINT, tml::shared_ptr<tml::graphic::Sampler> &);

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
 * @brief GetStage関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::ModelStage *tml::graphic::Model::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	auto index = static_cast<UINT>(type);

	if (index >= this->stage_cont_.size()) {
		return (nullptr);
	}

	return (this->stage_cont_[index].get());
}


/**
 * @brief GetRasterizerState関数
 * @param index (index)
 * @return rs (rasterizer_state)<br>
 * nullptr=失敗
 */
inline tml::graphic::RasterizerState *tml::graphic::Model::GetRasterizerState(const UINT index)
{
	if (index >= this->rs_cont_.size()) {
		return (nullptr);
	}

	return (this->rs_cont_[index].get());
}


/**
 * @brief GetBlendState関数
 * @param index (index)
 * @return bs (blend_state)<br>
 * nullptr=失敗
 */
inline tml::graphic::BlendState *tml::graphic::Model::GetBlendState(const UINT index)
{
	if (index >= this->bs_cont_.size()) {
		return (nullptr);
	}

	return (this->bs_cont_[index].get());
}


/**
 * @brief GetDepthState関数
 * @param index (index)
 * @return ds (depth_state)<br>
 * nullptr=失敗
 */
inline tml::graphic::DepthState *tml::graphic::Model::GetDepthState(const UINT index)
{
	if (index >= this->ds_cont_.size()) {
		return (nullptr);
	}

	return (this->ds_cont_[index].get());
}


/**
 * @brief GetShader関数
 * @param index (index)
 * @return shader (shader)<br>
 * nullptr=失敗
 */
inline tml::graphic::Shader *tml::graphic::Model::GetShader(const UINT index)
{
	if (index >= this->shader_cont_.size()) {
		return (nullptr);
	}

	return (this->shader_cont_[index].get());
}


/**
 * @brief GetMesh関数
 * @param index (index)
 * @return mesh (mesh)<br>
 * nullptr=失敗
 */
inline tml::graphic::Mesh *tml::graphic::Model::GetMesh(const UINT index)
{
	if (index >= this->mesh_cont_.size()) {
		return (nullptr);
	}

	return (this->mesh_cont_[index].get());
}


/**
 * @brief GetMaterial関数
 * @param index (index)
 * @return material (material)<br>
 * nullptr=失敗
 */
inline tml::graphic::Material *tml::graphic::Model::GetMaterial(const UINT index)
{
	if (index >= this->material_cont_.size()) {
		return (nullptr);
	}

	return (this->material_cont_[index].get());
}


/**
 * @brief GetTexture関数
 * @param index (index)
 * @return tex (texture)<br>
 * nullptr=失敗
 */
inline tml::graphic::Texture *tml::graphic::Model::GetTexture(const UINT index)
{
	if (index >= this->tex_cont_.size()) {
		return (nullptr);
	}

	return (this->tex_cont_[index].get());
}


/**
 * @brief GetSampler関数
 * @param index (index)
 * @return samp (sampler)<br>
 * nullptr=失敗
 */
inline tml::graphic::Sampler *tml::graphic::Model::GetSampler(const UINT index)
{
	if (index >= this->samp_cont_.size()) {
		return (nullptr);
	}

	return (this->samp_cont_[index].get());
}
