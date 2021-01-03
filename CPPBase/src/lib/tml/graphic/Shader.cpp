/**
 * @file
 * @brief Shader�R�[�h�t�@�C��
 */


#include "Shader.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ShaderDesc::ShaderDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ShaderDesc::~ShaderDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ShaderDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Shader::Shader()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Shader::~Shader()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Shader::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Shader::Init(void)
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
INT tml::Shader::Create(const tml::ShaderDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
