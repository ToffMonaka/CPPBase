/**
 * @file
 * @brief ManagerResource�R�[�h�t�@�C��
 */


#include "ManagerResource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerResourceDesc::ManagerResourceDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->name.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerResource::ManagerResource() :
	res_main_index_(0U),
	res_sub_index_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerResource::~ManagerResource()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerResource::Init(void)
{
	this->res_main_index_ = 0U;
	this->res_sub_index_ = 0U;
	this->name_.clear();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param res_main_index (resource_main_index)
 * @param res_sub_index (resource_sub_index)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ManagerResource::Create(const tml::ManagerResourceDesc &desc, const UINT res_main_index, const UINT res_sub_index)
{
	this->res_main_index_ = res_main_index;
	this->res_sub_index_ = res_sub_index;
	this->name_ = desc.name;

	return (0);
}
