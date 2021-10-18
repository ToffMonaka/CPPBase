/**
 * @file
 * @brief SceneEventコードファイル
 */


#include "SceneEvent.h"
#include "Manager.h"
#include "Scene.h"


/**
 * @brief コンストラクタ
 */
tml::scene::SceneEventData::SceneEventData() :
	type(tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::SceneEventData::~SceneEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::SceneEventData::Init(void)
{
	this->Release();

	this->type = tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::NONE;
	this->scene.reset();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::scene::SceneEventDesc::SceneEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::SceneEventDesc::~SceneEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::SceneEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::scene::ManagerEventDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::SceneEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::ManagerEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SceneEvent Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SCENE_EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::SceneEvent::SceneEvent() :
	type_(tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::SceneEvent::~SceneEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::SceneEvent::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE::NONE;
	this->data.Init();

	tml::scene::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::SceneEvent::Create(const tml::scene::SceneEventDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerEvent::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE>(this->GetEventSubIndex());
	this->data = desc.data;

	return (0);
}
