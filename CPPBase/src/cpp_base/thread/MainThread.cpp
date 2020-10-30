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

	return (0);
}


/**
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::MainThread::Start(void)
{
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
	return;
}
