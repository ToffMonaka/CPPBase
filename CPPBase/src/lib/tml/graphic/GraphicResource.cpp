/**
 * @file
 * @brief GraphicResource�R�[�h�t�@�C��
 */


#include "GraphicResource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::GraphicResourceDesc::GraphicResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::GraphicResourceDesc::~GraphicResourceDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::GraphicResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::GraphicResource::GraphicResource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::GraphicResource::~GraphicResource()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::GraphicResource::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::GraphicResource::Init(void)
{
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::GraphicResource::Create(const tml::GraphicResourceDesc &desc)
{
	this->mgr_ = desc.manager;

	return (0);
}
