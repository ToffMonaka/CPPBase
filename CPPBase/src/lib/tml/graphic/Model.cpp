/**
 * @file
 * @brief Modelコードファイル
 */


#include "Model.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::ModelDesc::ModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ModelDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Model::Model()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Model::~Model()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::Model::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Model::Init(void)
{
	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Model::Create(tml::ModelDesc &desc)
{
	if (tml::GraphicResource::Create(desc) < 0) {
		return (-1);
	}

	return (0);
}
