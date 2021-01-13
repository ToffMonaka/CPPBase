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
	res_type_(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE),
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
	this->res_type_ = tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE;
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param res_type (resource_type)
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Resource::Create(const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type, tml::graphic::ResourceDesc &desc)
{
	if ((res_type == tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;

	return (0);
}
