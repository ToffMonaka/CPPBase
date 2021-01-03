/**
 * @file
 * @brief Material�R�[�h�t�@�C��
 */


#include "Material.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MaterialDesc::MaterialDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MaterialDesc::~MaterialDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::MaterialDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Material::Material()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Material::~Material()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Material::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Material::Init(void)
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
INT tml::Material::Create(const tml::MaterialDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
