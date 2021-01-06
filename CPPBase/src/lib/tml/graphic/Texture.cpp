/**
 * @file
 * @brief Textureコードファイル
 */


#include "Texture.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::TextureDesc::TextureDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextureDesc::~TextureDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::TextureDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Texture::Texture()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Texture::~Texture()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Texture::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Texture::Init(void)
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
INT tml::Texture::Create(tml::TextureDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
