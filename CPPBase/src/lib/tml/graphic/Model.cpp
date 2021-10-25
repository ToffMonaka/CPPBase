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
#include "Canvas.h"


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
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ModelLayer::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelLayer::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->mesh_index_ = 0U;
	this->diffuse_tex_index_ = 0U;
	this->diffuse_samp_index_ = 0U;

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
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
	this->layer_cont_.resize(0U);

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelStage::~ModelStage()
{
	this->Release();

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

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelStage::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->rs_index_ = 0U;
	this->bs_index_ = 0U;
	this->ds_index_ = 0U;
	this->shader_index_ = 0U;
	this->layer_cont_.clear();
	this->layer_cont_.resize(0U);

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
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
	if (index >= this->layer_cont_.size()) {
		this->layer_cont_.resize(index + 1U);
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
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ModelDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Model Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MODEL");

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
	type_(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE),
	draw_set_canvas_cnt_(0U)
{
	this->stage_cont_.resize(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE_COUNT);

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model::~Model()
{
	this->Release();

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

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE;
	this->rs_cont_.clear();
	this->bs_cont_.clear();
	this->ds_cont_.clear();
	this->shader_cont_.clear();
	this->mesh_cont_.clear();
	this->tex_cont_.clear();
	this->samp_cont_.clear();
	this->stage_cont_.clear();
	this->stage_cont_.resize(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE_COUNT);
	this->draw_set_canvas_cnt_ = 0U;
	this->draw_set_canvas_cont_.clear();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model::Create(const tml::graphic::ModelDesc &desc)
{
	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::GRAPHIC::MODEL_TYPE>(this->GetResourceSubIndex());

	return (0);
}


/**
 * @brief SetRasterizerState関数
 * @param index (index)
 * @param rs (rasterizer_state)
 */
void tml::graphic::Model::SetRasterizerState(const UINT index, const tml::shared_ptr<tml::graphic::RasterizerState> &rs)
{
	if (index >= this->rs_cont_.size()) {
		this->rs_cont_.resize(index + 1U);
	}

	this->rs_cont_[index] = rs;

	return;
}


/**
 * @brief SetBlendState関数
 * @param index (index)
 * @param bs (blend_state)
 */
void tml::graphic::Model::SetBlendState(const UINT index, const tml::shared_ptr<tml::graphic::BlendState> &bs)
{
	if (index >= this->bs_cont_.size()) {
		this->bs_cont_.resize(index + 1U);
	}

	this->bs_cont_[index] = bs;

	return;
}


/**
 * @brief SetDepthState関数
 * @param index (index)
 * @param ds (depth_state)
 */
void tml::graphic::Model::SetDepthState(const UINT index, const tml::shared_ptr<tml::graphic::DepthState> &ds)
{
	if (index >= this->ds_cont_.size()) {
		this->ds_cont_.resize(index + 1U);
	}

	this->ds_cont_[index] = ds;

	return;
}


/**
 * @brief SetShader関数
 * @param index (index)
 * @param shader (shader)
 */
void tml::graphic::Model::SetShader(const UINT index, const tml::shared_ptr<tml::graphic::Shader> &shader)
{
	if (index >= this->shader_cont_.size()) {
		this->shader_cont_.resize(index + 1U);
	}

	this->shader_cont_[index] = shader;

	return;
}


/**
 * @brief SetMesh関数
 * @param index (index)
 * @param mesh (mesh)
 */
void tml::graphic::Model::SetMesh(const UINT index, const tml::shared_ptr<tml::graphic::Mesh> &mesh)
{
	if (index >= this->mesh_cont_.size()) {
		this->mesh_cont_.resize(index + 1U);
	}

	this->mesh_cont_[index] = mesh;

	return;
}


/**
 * @brief SetTexture関数
 * @param index (index)
 * @param tex (texture)
 */
void tml::graphic::Model::SetTexture(const UINT index, const tml::shared_ptr<tml::graphic::Texture> &tex)
{
	if (index >= this->tex_cont_.size()) {
		this->tex_cont_.resize(index + 1U);
	}

	this->tex_cont_[index] = tex;

	return;
}


/**
 * @brief SetSampler関数
 * @param index (index)
 * @param samp (sampler)
 */
void tml::graphic::Model::SetSampler(const UINT index, const tml::shared_ptr<tml::graphic::Sampler> &samp)
{
	if (index >= this->samp_cont_.size()) {
		this->samp_cont_.resize(index + 1U);
	}

	this->samp_cont_[index] = samp;

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
 * @brief IsHitByMouseDevice関数
 * @param mouse_device_pos (mouse_device_position)
 * @return hit_flg (hit_flag)
 */
bool tml::graphic::Model::IsHitByMouseDevice(const tml::XMINT2EX &mouse_device_pos)
{
	return (false);
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
 * @brief DrawStageDeferred3DShadow関数
 */
void tml::graphic::Model::DrawStageDeferred3DShadow(void)
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
