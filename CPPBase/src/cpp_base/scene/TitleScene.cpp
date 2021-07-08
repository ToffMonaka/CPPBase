/**
 * @file
 * @brief TitleSceneコードファイル
 */


#include "TitleScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/KeyboardDeviceEvent.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Camera2D.h"
#include "../../lib/tml/graphic/Camera3D.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::TitleSceneDesc::TitleSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::TitleSceneDesc::~TitleSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleSceneDesc::Init(void)
{
	this->Release();

	cpp_base::scene::BaseSceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseSceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// TitleScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"TITLE_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::TitleScene::TitleScene()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::TitleScene::~TitleScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::TitleScene::Release(void)
{
	cpp_base::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleScene::Init(void)
{
	this->Release();

	this->canvas_2d.reset();
	this->camera_2d.reset();
	this->camera_3d.reset();

	cpp_base::scene::BaseScene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleScene::Create(const cpp_base::scene::TitleSceneDesc &desc)
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
		desc.resource_name = L"canvas_2d";

		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Camera2D Create
		tml::graphic::Camera2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_PROJECTION_TYPE::ORTHOGRAPHIC;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));

		if (graphic_mgr->GetResource<tml::graphic::Camera2D>(this->camera_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Camera3D Create
		tml::graphic::Camera3DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_PROJECTION_TYPE::PERSPECTIVE;
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
 * @brief OnStart関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleScene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::TitleScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::TitleScene::OnUpdate(void)
{
	auto input_mgr = this->GetManager()->GetInputManager();
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	for (UINT event_i = 0U; event_i < input_mgr->GetEventCount(tml::input::DeviceEvent::EVENT_MAIN_INDEX); ++event_i) {
		auto event = reinterpret_cast<tml::input::DeviceEvent *>(input_mgr->GetEventFast(tml::input::DeviceEvent::EVENT_MAIN_INDEX, event_i));

		switch (event->GetEventSubIndex()) {
		case tml::input::KeyboardDeviceEvent::EVENT_SUB_INDEX: {
			auto &event_dat = reinterpret_cast<tml::input::KeyboardDeviceEvent *>(event)->data;

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::BUTTON_DOWN)) {
				if (event_dat.code == tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::W) {
					this->camera_2d->position.SetY(this->camera_2d->position.GetY() + 2.0f);
				} else if (event_dat.code == tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S) {
					this->camera_2d->position.SetY(this->camera_2d->position.GetY() - 2.0f);
				}

				if (event_dat.code == tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A) {
					this->camera_2d->position.SetX(this->camera_2d->position.GetX() + 2.0f);
				} else if (event_dat.code == tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D) {
					this->camera_2d->position.SetX(this->camera_2d->position.GetX() - 2.0f);
				}

				if (event_dat.code == tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::Q) {
					auto angle = this->camera_2d->position.GetAngle();

					angle -= tml::MathUtil::GetAngleRadian(2.0f);

					this->camera_2d->position.SetAngle(angle);
				} else if (event_dat.code == tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::E) {
					auto angle = this->camera_2d->position.GetAngle();

					angle += tml::MathUtil::GetAngleRadian(2.0f);

					this->camera_2d->position.SetAngle(angle);
				}
			}

			break;
		}
		}
	}

	this->canvas_2d->SetDrawCamera(this->camera_2d.get());

	graphic_mgr->SetDrawCanvas(this->canvas_2d.get());

	return;
}
