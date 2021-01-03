/**
 * @file
 * @brief Mesh�R�[�h�t�@�C��
 */


#include "Mesh.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MeshDesc::MeshDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MeshDesc::~MeshDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::MeshDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Mesh::Mesh()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Mesh::~Mesh()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Mesh::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Mesh::Init(void)
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
INT tml::Mesh::Create(const tml::MeshDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
