/**
 * @file
 * @brief Light�R�[�h�t�@�C��
 */


#include "Light.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::LightDesc::LightDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::LightDesc::~LightDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::LightDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Light::Light()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Light::~Light()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Light::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Light::Init(void)
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
INT tml::Light::Create(const tml::LightDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
