/**
 * @file
 * @brief Materialコードファイル
 */


#include "Material.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::MaterialDesc::MaterialDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MaterialDesc::~MaterialDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::MaterialDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Material::Material()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Material::~Material()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Material::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Material::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Material::Create(const tml::MaterialDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
