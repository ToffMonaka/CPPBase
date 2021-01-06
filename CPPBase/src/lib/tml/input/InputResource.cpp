/**
 * @file
 * @brief InputResource�R�[�h�t�@�C��
 */


#include "InputResource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::InputResourceDesc::InputResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::InputResourceDesc::~InputResourceDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::InputResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::InputResource::InputResource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::InputResource::~InputResource()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::InputResource::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::InputResource::Init(void)
{
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::InputResource::Create(tml::InputResourceDesc &desc)
{
	if (desc.manager == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.manager;

	return (0);
}
