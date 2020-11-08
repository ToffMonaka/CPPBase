/**
 * @file
 * @brief MainThread�R�[�h�t�@�C��
 */


#include "MainThread.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::MainThread::MainThread()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::MainThread::~MainThread()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::MainThread::Release(void)
{
	tml::Thread::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::MainThread::Init(void)
{
	this->Release();

	this->frame_rate_.Init();

	tml::Thread::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::MainThread::Create(void)
{
	this->Release();

	if (tml::Thread::Create() < 0) {
		this->Init();

		return (-1);
	}

	this->frame_rate_.Init();

	return (0);
}


/**
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::MainThread::Start(void)
{
	this->frame_rate_.Start(60U);

	return (0);
}


/**
 * @brief End�֐�
 */
void cpp_base::MainThread::End(void)
{
	return;
}


/**
 * @brief Update�֐�
 */
void cpp_base::MainThread::Update(void)
{
	this->frame_rate_.Update();

	return;
}
