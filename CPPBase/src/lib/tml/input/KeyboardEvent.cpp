/**
 * @file
 * @brief KeyboardEvent�R�[�h�t�@�C��
 */


#include "KeyboardEvent.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardEventData::KeyboardEventData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardEventData::~KeyboardEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardEventData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardEvent::KeyboardEvent()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardEvent::~KeyboardEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardEvent::Init(void)
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
INT tml::input::KeyboardEvent::Create(tml::input::Manager *mgr)
{
	this->Init();

	if (tml::input::Event::Create(tml::input::KeyboardEvent::EVENT_TYPE, mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
