/**
 * @file
 * @brief Modelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMath.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelDescクラス
 */
class ModelDesc : public tml::graphic::ResourceDesc
{
public:
	tml::XMPosition position;
	bool position_set_flag;

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ModelDesc();
	virtual ~ModelDesc();

	virtual void Init(void);
};
}
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
	std::vector<tml::shared_ptr<tml::graphic::RasterizerState>> rs_cont_;
	std::vector<tml::shared_ptr<tml::graphic::BlendState>> bs_cont_;
	std::vector<tml::shared_ptr<tml::graphic::DepthState>> ds_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Shader>> shader_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Mesh>> mesh_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Material>> material_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Texture>> tex_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Sampler>> samp_cont_;

public:
	tml::shared_ptr<tml::XMPosition> position;

protected:
	void Release(void);
	INT Create(const tml::graphic::ModelDesc &, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE, tml::shared_ptr<tml::XMPosition> *pos = nullptr);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::MODEL_TYPE GetType(void) const;
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
