/**
 * @file
 * @brief Clock�R�[�h�t�@�C��
 */


#include "Clock.h"


/**
 * @brief �R���X�g���N�^
 */
tml::Clock::Clock() :
	time_(0LL)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Clock::~Clock()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Clock::Init(void)
{
	this->Release();

	this->time_ = tml::TIME_MILLI(0LL);

	return;
}


/**
 * @brief SetTime�֐�
 * @param time (time)
 */
void tml::Clock::SetTime(const tml::TIME_MILLI &time)
{
	this->time_ = time;

	return;
}
