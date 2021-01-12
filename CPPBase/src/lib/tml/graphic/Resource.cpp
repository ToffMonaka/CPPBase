/**
 * @file
 * @brief Resource�R�[�h�t�@�C��
 */


#include "Resource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ResourceDesc::~ResourceDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Resource::Resource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Resource::~Resource()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::Resource::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Resource::Init(void)
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
INT tml::graphic::Resource::Create(tml::graphic::ResourceDesc &desc)
{
	if (desc.manager == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.manager;

	return (0);
}
