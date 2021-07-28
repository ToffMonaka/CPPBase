/**
 * @file
 * @brief SceneEvent�R�[�h�t�@�C��
 */


#include "SceneEvent.h"
#include "Manager.h"
#include "Scene.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::SceneEventData::SceneEventData() :
	type(tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::SceneEventData::~SceneEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::SceneEventData::Init(void)
{
	this->Release();

	this->type = tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::NONE;
	this->scene.reset();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::SceneEventDesc::SceneEventDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::SceneEventDesc::~SceneEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::SceneEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::scene::ManagerEventDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::SceneEvent::SceneEvent() :
	type_(tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::SceneEvent::~SceneEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
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
