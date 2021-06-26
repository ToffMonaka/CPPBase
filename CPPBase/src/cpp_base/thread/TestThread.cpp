/**
 * @file
 * @brief TestThread�R�[�h�t�@�C��
 */


#include "TestThread.h"
#include "../../lib/tml/time/TimeUtil.h"


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
 * @brief OnStart�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::TestThread::OnStart(void)
{
	{// COM Create
		if (this->CreateCOM() < 0) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::TestThread::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::TestThread::OnUpdate(void)
{
	tml::TimeUtil::Sleep(tml::TIME_REAL(0.1));

	return;
}
