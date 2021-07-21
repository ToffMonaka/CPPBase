/**
 * @file
 * @brief StageScene�R�[�h�t�@�C��
 */


#include "StageScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Camera2D.h"
#include "../../lib/tml/graphic/Camera3D.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::StageSceneDesc::StageSceneDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::StageSceneDesc::~StageSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::StageSceneDesc::Init(void)
{
	this->Release();

	cpp_base::scene::BaseSceneDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::StageSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseSceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// StageScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"STAGE_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::StageScene::StageScene()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::StageScene::~StageScene()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::StageScene::Release(void)
{
	cpp_base::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::StageScene::Init(void)
{
	this->Release();

	this->canvas_2d.reset();
	this->camera_2d.reset();
	this->camera_3d.reset();

	cpp_base::scene::BaseScene::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::StageScene::Create(const cpp_base::scene::StageSceneDesc &desc)
{
	this->Init();

	if (cpp_base::scene::BaseScene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	{// Canvas2D Create
		tml::graphic::Canvas2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.resource_name = L"Canvas2D";

		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		this->canvas_2d->SetRenderTargetTexture(graphic_mgr->common.main_render_target_texture);
		this->canvas_2d->SetRenderTargetTextureClearFlag(true);
	}

	{// Camera2D Create
		tml::graphic::Camera2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::ORTHOGRAPHIC;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));

		if (graphic_mgr->GetResource<tml::graphic::Camera2D>(this->camera_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Camera3D Create
		tml::graphic::Camera3DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::PERSPECTIVE;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		desc.near_clip = 0.1f;
		desc.far_clip = 1000.0f;

		if (graphic_mgr->GetResource<tml::graphic::Camera3D>(this->camera_3d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::StageScene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::StageScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::StageScene::OnUpdate(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->canvas_2d->SetDrawCamera(this->camera_2d.get());

	graphic_mgr->SetDrawCanvas(this->canvas_2d.get());

	return;
}
