/**
 * @file
 * @brief Model�R�[�h�t�@�C��
 */


#include "Model.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ModelDesc::ModelDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ModelDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Model::Model()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Model::~Model()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::Model::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Model::Init(void)
{
	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::Model::Create(tml::ModelDesc &desc)
{
	if (tml::GraphicResource::Create(desc) < 0) {
		return (-1);
	}

	return (0);
}
