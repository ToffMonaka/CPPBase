/**
 * @file
 * @brief ScreenModelコードファイル
 */


#include "ScreenModel.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ScreenModelDesc::ScreenModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ScreenModelDesc::~ScreenModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ScreenModelDesc::Init(void)
{
	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief コンストラクタ
 */
tml::graphic::ScreenModel::ScreenModel()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ScreenModel::~ScreenModel()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ScreenModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ScreenModel::Init(void)
{
	this->Release();

	tml::graphic::Model::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param pos (position)<br>
 * nullptr=指定無し
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ScreenModel::Create(const tml::graphic::ScreenModelDesc &desc, tml::shared_ptr<tml::XMPosition> *pos)
{
	this->Init();

	if (tml::graphic::Model::Create(desc, tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SCREEN, pos) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
