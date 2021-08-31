/**
 * @file
 * @brief StageSceneコードファイル
 */


#include "StageScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Camera2D.h"
#include "../../lib/tml/graphic/Camera3D.h"
#include "../../lib/tml/scene/Node.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::StageSceneDesc::StageSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::StageSceneDesc::~StageSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::StageSceneDesc::Init(void)
{
	this->Release();

	cpp_base::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageSceneDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::SceneDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// StageScene Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"STAGE_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::StageScene::StageScene() :
	progress_type_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::StageScene::~StageScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::StageScene::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::StageScene::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;

	this->canvas_2d.reset();
	this->camera_2d.reset();
	this->camera_3d.reset();
	this->main_node.reset();
	this->stage_layout_node.reset();
	this->stage_node.reset();

	cpp_base::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageScene::Create(const cpp_base::scene::StageSceneDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Scene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// Canvas2D Create
		tml::graphic::Canvas2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.resource_name = L"Canvas2D";

		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		this->canvas_2d->SetRenderTargetTexture(this->GetGraphicManager()->common.main_render_target_texture);
		this->canvas_2d->SetRenderTargetTextureClearFlag(true);
	}

	{// Camera2D Create
		tml::graphic::Camera2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::ORTHOGRAPHIC;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Camera2D>(this->camera_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Camera3D Create
		tml::graphic::Camera3DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::PERSPECTIVE;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		desc.near_clip = 0.1f;
		desc.far_clip = 1000.0f;

		if (this->GetGraphicManager()->GetResource<tml::graphic::Camera3D>(this->camera_3d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageScene::OnStart(void)
{
	this->progress_type_ = 1U;

	{// MainNode Create
		this->main_node = this->GetRootNode()->GetChildNode(L"main");

		if (this->main_node == nullptr) {
			return (-1);
		}
	}

	{// StageLayoutNode Create
		this->stage_layout_node = this->GetRootNode()->GetChildNode(L"stage_layout");

		if (this->stage_layout_node == nullptr) {
			return (-1);
		}
	}

	{// StageNode Create
		if (this->GetManager()->GetNode(this->stage_node, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::TEST_2D_STAGE_NODE_PREFAB)) == nullptr) {
			return (-1);
		}

		this->stage_layout_node->AddChildNode(this->stage_node);
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::StageScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::StageScene::OnUpdate(void)
{
	switch (this->progress_type_) {
	case 1U: {
		break;
	}
	}

	this->canvas_2d->SetDrawCamera(this->camera_2d.get());

	this->GetGraphicManager()->SetDrawCanvas(this->canvas_2d.get());

	return;
}
