/**
 * @file
 * @brief Resource�R�[�h�t�@�C��
 */


#include "Resource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ResourceDesc::~ResourceDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::Resource::Resource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::Resource::~Resource()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::input::Resource::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::Resource::Init(void)
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
INT tml::input::Resource::Create(tml::input::ResourceDesc &desc)
{
	if (desc.manager == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.manager;

	return (0);
}
