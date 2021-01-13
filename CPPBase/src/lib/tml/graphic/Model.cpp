/**
 * @file
 * @brief Model�R�[�h�t�@�C��
 */


#include "Model.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelDesc::ModelDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelDesc::Init(void)
{
	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Model::Model()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Model::~Model()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::Model::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Model::Init(void)
{
	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Model::Create(tml::graphic::ModelDesc &desc)
{
	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MODEL, desc) < 0) {
		return (-1);
	}

	return (0);
}
