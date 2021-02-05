/**
 * @file
 * @brief Modelコードファイル
 */


#include "Model.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelDesc::ModelDesc() :
	position_set_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelDesc::Init(void)
{
	this->position.Init();
	this->position_set_flag = true;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ModelDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Model Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"MODEL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model::Model() :
	type_(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model::~Model()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model::Release(void)
{
	if (this->GetManager() != nullptr) {
		for (auto &rs : this->rs_cont_) {
			this->GetManager()->ReleaseResource(rs);
		}

		this->rs_cont_.clear();

		for (auto &bs : this->bs_cont_) {
			this->GetManager()->ReleaseResource(bs);
		}

		this->bs_cont_.clear();

		for (auto &ds : this->ds_cont_) {
			this->GetManager()->ReleaseResource(ds);
		}

		this->ds_cont_.clear();

		for (auto &shader : this->shader_cont_) {
			this->GetManager()->ReleaseResource(shader);
		}

		this->shader_cont_.clear();

		for (auto &mesh : this->mesh_cont_) {
			this->GetManager()->ReleaseResource(mesh);
		}

		this->mesh_cont_.clear();

		for (auto &material : this->material_cont_) {
			this->GetManager()->ReleaseResource(material);
		}

		this->material_cont_.clear();

		for (auto &tex : this->tex_cont_) {
			this->GetManager()->ReleaseResource(tex);
		}

		this->tex_cont_.clear();

		for (auto &samp : this->samp_cont_) {
			this->GetManager()->ReleaseResource(samp);
		}

		this->samp_cont_.clear();
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE;
	this->position.reset();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @param pos (position)<br>
 * nullptr=指定無し
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model::Create(const tml::graphic::ModelDesc &desc, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE type, tml::shared_ptr<tml::XMPosition> *pos)
{
	if (type == tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MODEL) < 0) {
		return (-1);
	}

	this->type_ = type;

	if ((pos != nullptr)
	&& ((*pos) != nullptr)) {
		this->position = (*pos);
	} else {
		this->position = tml::make_shared<tml::XMPosition>(1U);
	}

	if (desc.position_set_flag) {
		(*this->position) = desc.position;
	}

	return (0);
}


/**
 * @brief SetRasterizerState関数
 * @param index (index)
 * @param rs (rasterizer_state)
 */
void tml::graphic::Model::SetRasterizerState(const UINT index, tml::shared_ptr<tml::graphic::RasterizerState> &rs)
{
	while (index >= this->rs_cont_.size()) {
		this->rs_cont_.push_back(tml::make_shared<tml::graphic::RasterizerState>());
	}

	this->GetManager()->GetResource(this->rs_cont_[index], rs);

	return;
}


/**
 * @brief SetBlendState関数
 * @param index (index)
 * @param bs (blend_state)
 */
void tml::graphic::Model::SetBlendState(const UINT index, tml::shared_ptr<tml::graphic::BlendState> &bs)
{
	while (index >= this->bs_cont_.size()) {
		this->bs_cont_.push_back(tml::make_shared<tml::graphic::BlendState>());
	}

	this->GetManager()->GetResource(this->bs_cont_[index], bs);

	return;
}


/**
 * @brief SetDepthState関数
 * @param index (index)
 * @param ds (depth_state)
 */
void tml::graphic::Model::SetDepthState(const UINT index, tml::shared_ptr<tml::graphic::DepthState> &ds)
{
	while (index >= this->ds_cont_.size()) {
		this->ds_cont_.push_back(tml::make_shared<tml::graphic::DepthState>());
	}

	this->GetManager()->GetResource(this->ds_cont_[index], ds);

	return;
}


/**
 * @brief SetShader関数
 * @param index (index)
 * @param shader (shader)
 */
void tml::graphic::Model::SetShader(const UINT index, tml::shared_ptr<tml::graphic::Shader> &shader)
{
	while (index >= this->shader_cont_.size()) {
		this->shader_cont_.push_back(tml::make_shared<tml::graphic::Shader>());
	}

	this->GetManager()->GetResource(this->shader_cont_[index], shader);

	return;
}


/**
 * @brief SetMesh関数
 * @param index (index)
 * @param mesh (mesh)
 */
void tml::graphic::Model::SetMesh(const UINT index, tml::shared_ptr<tml::graphic::Mesh> &mesh)
{
	while (index >= this->mesh_cont_.size()) {
		this->mesh_cont_.push_back(tml::make_shared<tml::graphic::Mesh>());
	}

	this->GetManager()->GetResource(this->mesh_cont_[index], mesh);

	return;
}


/**
 * @brief SetMaterial関数
 * @param index (index)
 * @param material (material)
 */
void tml::graphic::Model::SetMaterial(const UINT index, tml::shared_ptr<tml::graphic::Material> &material)
{
	while (index >= this->material_cont_.size()) {
		this->material_cont_.push_back(tml::make_shared<tml::graphic::Material>());
	}

	this->GetManager()->GetResource(this->material_cont_[index], material);

	return;
}


/**
 * @brief SetTexture関数
 * @param index (index)
 * @param tex (texture)
 */
void tml::graphic::Model::SetTexture(const UINT index, tml::shared_ptr<tml::graphic::Texture> &tex)
{
	while (index >= this->tex_cont_.size()) {
		this->tex_cont_.push_back(tml::make_shared<tml::graphic::Texture>());
	}

	this->GetManager()->GetResource(this->tex_cont_[index], tex);

	return;
}


/**
 * @brief SetSampler関数
 * @param index (index)
 * @param samp (sampler)
 */
void tml::graphic::Model::SetSampler(const UINT index, tml::shared_ptr<tml::graphic::Sampler> &samp)
{
	while (index >= this->samp_cont_.size()) {
		this->samp_cont_.push_back(tml::make_shared<tml::graphic::Sampler>());
	}

	this->GetManager()->GetResource(this->samp_cont_[index], samp);

	return;
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::Model::DrawStageInit(void)
{
	return;
}


/**
 * @brief DrawStageDeferred3D関数
 */
void tml::graphic::Model::DrawStageDeferred3D(void)
{
	return;
}


/**
 * @brief DrawStageDeferredShadow3D関数
 */
void tml::graphic::Model::DrawStageDeferredShadow3D(void)
{
	return;
}


/**
 * @brief DrawStageForward3D関数
 */
void tml::graphic::Model::DrawStageForward3D(void)
{
	return;
}


/**
 * @brief DrawStageForward2D関数
 */
void tml::graphic::Model::DrawStageForward2D(void)
{
	return;
}
