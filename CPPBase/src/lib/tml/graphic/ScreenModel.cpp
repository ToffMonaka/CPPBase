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
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ScreenModel::Create(tml::graphic::ScreenModelDesc &desc)
{
	this->Init();

	if (tml::graphic::Model::Create(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SCREEN, desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
