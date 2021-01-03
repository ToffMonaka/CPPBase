/**
 * @file
 * @brief Fog�R�[�h�t�@�C��
 */


#include "Fog.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::FogDesc::FogDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FogDesc::~FogDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::FogDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Fog::Fog()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Fog::~Fog()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Fog::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Fog::Init(void)
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
INT tml::Fog::Create(const tml::FogDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
