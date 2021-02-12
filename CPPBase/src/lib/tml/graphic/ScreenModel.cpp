/**
 * @file
 * @brief ScreenModel�R�[�h�t�@�C��
 */


#include "ScreenModel.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ScreenModelLayer::ScreenModelLayer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ScreenModelLayer::~ScreenModelLayer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ScreenModelLayer::Init(void)
{
	this->Release();

	tml::graphic::ModelLayer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ScreenModelLayer::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::ModelLayer::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ScreenModelStage::ScreenModelStage()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ScreenModelStage::~ScreenModelStage()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ScreenModelStage::Init(void)
{
	this->Release();

	tml::graphic::ModelStage::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ScreenModelStage::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::ModelStage::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


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
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ScreenModelDesc::Init(void)
{
	this->Release();

	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ScreenModelDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ModelDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// ScreenModel Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SCREEN_MODEL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
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
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ScreenModel::Create(const tml::graphic::ScreenModelDesc &desc)
{
	this->Init();

	if (tml::graphic::Model::Create(desc, tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SCREEN) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
