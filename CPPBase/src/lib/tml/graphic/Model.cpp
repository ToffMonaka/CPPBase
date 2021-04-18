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
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelLayer::ModelLayer() :
	mgr_(nullptr),
	mesh_index_(0U),
	diffuse_tex_index_(0U),
	diffuse_samp_index_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelLayer::~ModelLayer()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelLayer::Init(void)
{
	this->mgr_ = nullptr;
	this->mesh_index_ = 0U;
	this->diffuse_tex_index_ = 0U;
	this->diffuse_samp_index_ = 0U;

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ModelLayer::Create(tml::graphic::Manager *mgr)
{
	if (mgr == nullptr) {
		return (-1);
	}

	this->mgr_ = mgr;

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelStage::ModelStage() :
	mgr_(nullptr),
	rs_index_(0U),
	bs_index_(0U),
	ds_index_(0U),
	shader_index_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelStage::~ModelStage()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ModelStage::Release(void)
{
	for (auto &layer : this->layer_cont_) {
		layer.reset();
	}

	this->layer_cont_.clear();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelStage::Init(void)
{
	this->mgr_ = nullptr;
	this->rs_index_ = 0U;
	this->bs_index_ = 0U;
	this->ds_index_ = 0U;
	this->shader_index_ = 0U;

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ModelStage::Create(tml::graphic::Manager *mgr)
{
	if (mgr == nullptr) {
		return (-1);
	}

	this->mgr_ = mgr;

	return (0);
}


/**
 * @brief SetLayer関数
 * @param index (index)
 * @param layer (layer)
 */
void tml::graphic::ModelStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::ModelLayer> &layer)
{
	while (index >= this->layer_cont_.size()) {
		this->layer_cont_.push_back(tml::make_unique<tml::graphic::ModelLayer>());
	}

	this->layer_cont_[index] = std::move(layer);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelDesc::ModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelDesc::~ModelDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerResourceDesc::Init();

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
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
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
	for (auto &stage : this->stage_cont_) {
		stage.reset();
	}

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

		for (auto &tex : this->tex_cont_) {
			this->GetManager()->ReleaseResource(tex);
		}

		this->tex_cont_.clear();

		for (auto &samp : this->samp_cont_) {
			this->GetManager()->ReleaseResource(samp);
		}

		this->samp_cont_.clear();
	}

	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model::Create(const tml::graphic::ModelDesc &desc, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE type)
{
	if (type == tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MODEL, 1U) < 0) {
		return (-1);
	}

	this->type_ = type;

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
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
void tml::graphic::Model::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::ModelStage> &stage)
{
	this->stage_cont_[static_cast<UINT>(type)] = std::move(stage);

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


#if 0
/**
 * @brief コンストラクタ
 */
tml::graphic::MaterialDesc::MaterialDesc() :
	diffuse_color(0.0f),
	diffuse_mul_value(0.0f),
	transparent_mul_value(0.0f),
	burn_mul_value(0.0f),
	emissive_mul_value(0.0f),
	bloom_mul_value(0.0f),
	specular_mul_value(0.0f),
	specular_exp_value(1.0f),
	rim_mul_value(0.0f),
	rim_exp_value(1.0f),
	light_flag(false),
	fog_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::MaterialDesc::~MaterialDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::MaterialDesc::Init(void)
{
	this->Release();

	this->diffuse_color = 0.0f;
	this->diffuse_mul_value = 0.0f;
	this->transparent_mul_value = 0.0f;
	this->burn_mul_value = 0.0f;
	this->emissive_mul_value = 0.0f;
	this->bloom_mul_value = 0.0f;
	this->specular_mul_value = 0.0f;
	this->specular_exp_value = 1.0f;
	this->rim_mul_value = 0.0f;
	this->rim_exp_value = 1.0f;
	this->light_flag = false;
	this->fog_flag = false;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::MaterialDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Material Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"MATERIAL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Material::Material() :
	diffuse_col_(0.0f),
	diffuse_mul_val_(0.0f),
	transparent_mul_val_(0.0f),
	burn_mul_val_(0.0f),
	emissive_mul_val_(0.0f),
	bloom_mul_val_(0.0f),
	specular_mul_val_(0.0f),
	specular_exp_val_(1.0f),
	rim_mul_val_(0.0f),
	rim_exp_val_(1.0f),
	light_flg_(false),
	fog_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Material::~Material()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Material::Init(void)
{
	this->Release();

	this->diffuse_col_ = 0.0f;
	this->diffuse_mul_val_ = 0.0f;
	this->transparent_mul_val_ = 0.0f;
	this->burn_mul_val_ = 0.0f;
	this->emissive_mul_val_ = 0.0f;
	this->bloom_mul_val_ = 0.0f;
	this->specular_mul_val_ = 0.0f;
	this->specular_exp_val_ = 1.0f;
	this->rim_mul_val_ = 0.0f;
	this->rim_exp_val_ = 1.0f;
	this->light_flg_ = false;
	this->fog_flg_ = false;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Material::Create(const tml::graphic::MaterialDesc &desc)
{
	this->Init();

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MATERIAL, 1U) < 0) {
		this->Init();

		return (-1);
	}

	this->diffuse_col_ = desc.diffuse_color;
	this->diffuse_mul_val_ = desc.diffuse_mul_value;
	this->transparent_mul_val_ = desc.transparent_mul_value;
	this->burn_mul_val_ = desc.burn_mul_value;
	this->emissive_mul_val_ = desc.emissive_mul_value;
	this->bloom_mul_val_ = desc.bloom_mul_value;
	this->specular_mul_val_ = desc.specular_mul_value;
	this->specular_exp_val_ = desc.specular_exp_value;
	this->rim_mul_val_ = desc.rim_mul_value;
	this->rim_exp_val_ = desc.rim_exp_value;
	this->light_flg_ = desc.light_flag;
	this->fog_flg_ = desc.fog_flag;

	return (0);
}
#endif
