/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEventDesc::ManagerEventDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEventDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEvent::ManagerEvent() :
	event_index_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEvent::Init(void)
{
	this->event_index_ = 0U;

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param event_index (event_index)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ManagerEvent::Create(const tml::ManagerEventDesc &desc, const UINT event_index)
{
	this->event_index_ = event_index;

	return (0);
}
