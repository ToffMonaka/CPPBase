/**
 * @file
 * @brief Modelコードファイル
 */


#include "Model.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelDesc::ModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelDesc::Init(void)
{
	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model::Model()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model::~Model()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model::Init(void)
{
	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model::Create(tml::graphic::ModelDesc &desc)
{
	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MODEL, desc) < 0) {
		return (-1);
	}

	return (0);
}
