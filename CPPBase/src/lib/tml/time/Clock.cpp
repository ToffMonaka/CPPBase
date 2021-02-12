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
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::Clock::Clock(const tml::Clock &src)
{
	this->time_ = src.time_;

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::Clock &tml::Clock::operator =(const tml::Clock &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->time_ = src.time_;

	return ((*this));
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::Clock::Clock(tml::Clock &&src) noexcept
{
	this->time_ = src.time_;

	src.Init();

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::Clock &tml::Clock::operator =(tml::Clock &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->time_ = src.time_;

	src.Init();

	return ((*this));
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
