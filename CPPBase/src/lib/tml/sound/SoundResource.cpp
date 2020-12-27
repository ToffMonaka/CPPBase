/**
 * @file
 * @brief SoundResource�R�[�h�t�@�C��
 */


#include "SoundResource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::SoundResourceDesc::SoundResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SoundResourceDesc::~SoundResourceDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::SoundResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::SoundResource::SoundResource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SoundResource::~SoundResource()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::SoundResource::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::SoundResource::Init(void)
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
INT tml::SoundResource::Create(const tml::SoundResourceDesc &desc)
{
	this->mgr_ = desc.manager;

	return (0);
}
