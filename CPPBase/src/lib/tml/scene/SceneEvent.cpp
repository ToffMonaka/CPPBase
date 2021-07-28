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

	if (tml::scene::ManagerEvent::Create(desc, tml::ConstantUtil::SCENE::EVENT_TYPE::SCENE, static_cast<UINT>(tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE::ETC)) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE::ETC;
	this->data = desc.data;

	return (0);
}
