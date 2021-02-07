/**
 * @file
 * @brief Timer�R�[�h�t�@�C��
 */


#include "Timer.h"


/**
 * @brief �R���X�g���N�^
 */
tml::Timer::Timer() :
	elapsed_time_(0.0),
	started_flg_(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Timer::~Timer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Timer::Init(void)
{
	this->Release();

	this->start_time_ = std::chrono::steady_clock::time_point();
	this->elapsed_time_ = tml::TIME_REAL(0.0);
	this->started_flg_ = false;

	return;
}


/**
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::Timer::Start(void)
{
	this->start_time_ = std::chrono::steady_clock::now();
	this->elapsed_time_ = tml::TIME_REAL(0.0);

	this->started_flg_ = true;

	return (0);
}


/**
 * @brief Stop�֐�
 */
void tml::Timer::Stop(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->start_time_);

	this->started_flg_ = false;

	return;
}
