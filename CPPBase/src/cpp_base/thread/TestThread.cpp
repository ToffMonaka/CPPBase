/**
 * @file
 * @brief TestThread�R�[�h�t�@�C��
 */


#include "TestThread.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::TestThread::TestThread()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::TestThread::~TestThread()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::TestThread::Release(void)
{
	this->DeleteCOM();

	tml::SubThread::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::TestThread::Init(void)
{
	this->Release();

	this->frame_rate_.Init();

	tml::SubThread::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::TestThread::Create(void)
{
	this->Init();

	if (tml::SubThread::Create() < 0) {
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
INT cpp_base::TestThread::Start(void)
{
	{// COM Create
		if (this->CreateCOM() < 0) {
			return (-1);
		}
	}

	this->frame_rate_.Start(60U);

	return (0);
}


/**
 * @brief End�֐�
 */
void cpp_base::TestThread::End(void)
{
	return;
}


/**
 * @brief Update�֐�
 */
void cpp_base::TestThread::Update(void)
{
	this->frame_rate_.Update();

	return;
}
