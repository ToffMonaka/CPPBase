/**
 * @file
 * @brief ScreenModel�R�[�h�t�@�C��
 */


#include "ScreenModel.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ScreenModelDesc::ScreenModelDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ScreenModelDesc::~ScreenModelDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ScreenModelDesc::Init(void)
{
	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ScreenModel::ScreenModel()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ScreenModel::~ScreenModel()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::ScreenModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ScreenModel::Init(void)
{
	this->Release();

	tml::graphic::Model::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param pos (position)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ScreenModel::Create(const tml::graphic::ScreenModelDesc &desc, tml::shared_ptr<tml::XMPosition> &pos)
{
	this->Init();

	if (tml::graphic::Model::Create(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SCREEN, desc, pos) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
