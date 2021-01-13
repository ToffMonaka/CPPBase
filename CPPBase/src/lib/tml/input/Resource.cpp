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
	res_type_(tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE),
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
	this->res_type_ = tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE;
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
INT tml::input::Resource::Create(const tml::ConstantUtil::INPUT::RESOURCE_TYPE res_type, tml::input::ResourceDesc &desc)
{
	if ((res_type == tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;

	return (0);
}
