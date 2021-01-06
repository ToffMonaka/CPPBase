/**
 * @file
 * @brief Texture�R�[�h�t�@�C��
 */


#include "Texture.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::TextureDesc::TextureDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextureDesc::~TextureDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextureDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Texture::Texture()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Texture::~Texture()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Texture::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Texture::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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
