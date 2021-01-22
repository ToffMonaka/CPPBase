/**
 * @file
 * @brief SpriteModel�R�[�h�t�@�C��
 */


#include "SpriteModel.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::SpriteModelDesc::SpriteModelDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::SpriteModelDesc::~SpriteModelDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::SpriteModelDesc::Init(void)
{
	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::SpriteModel::SpriteModel()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::SpriteModel::~SpriteModel()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::SpriteModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::SpriteModel::Init(void)
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
INT tml::graphic::SpriteModel::Create(const tml::graphic::SpriteModelDesc &desc, tml::shared_ptr<tml::XMPosition> &pos)
{
	this->Init();

	if (tml::graphic::Model::Create(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SPRITE, desc, pos) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
