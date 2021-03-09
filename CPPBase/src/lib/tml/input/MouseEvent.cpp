/**
 * @file
 * @brief MouseEvent�R�[�h�t�@�C��
 */


#include "MouseEvent.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::MouseEventData::MouseEventData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::MouseEventData::~MouseEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::MouseEventData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::MouseEvent::MouseEvent()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::MouseEvent::~MouseEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::MouseEvent::Init(void)
{
	this->Release();

	this->dat_.Init();

	tml::input::Event::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::MouseEvent::Create(tml::input::Manager *mgr)
{
	this->Init();

	if (tml::input::Event::Create(tml::input::MouseEvent::EVENT_TYPE, mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
