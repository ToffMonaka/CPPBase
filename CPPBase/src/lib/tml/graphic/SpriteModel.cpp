/**
 * @file
 * @brief SpriteModelコードファイル
 */


#include "SpriteModel.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelDesc::SpriteModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelDesc::~SpriteModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelDesc::Init(void)
{
	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModel::SpriteModel()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModel::~SpriteModel()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::SpriteModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModel::Init(void)
{
	this->Release();

	tml::graphic::Model::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param pos (position)
 * @return res (result)<br>
 * 0未満=失敗
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
