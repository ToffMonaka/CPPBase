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
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::SpriteModelDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ModelDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SpriteModel Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SPRITE_MODEL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
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
 * @param pos (position)<br>
 * nullptr=�w�薳��
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::SpriteModel::Create(const tml::graphic::SpriteModelDesc &desc, tml::shared_ptr<tml::XMPosition> *pos)
{
	this->Init();

	if (tml::graphic::Model::Create(desc, tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SPRITE, pos) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
