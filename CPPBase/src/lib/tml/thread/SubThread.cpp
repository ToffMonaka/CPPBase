/**
 * @file
 * @brief SubThread�R�[�h�t�@�C��
 */


#include "SubThread.h"
#include "ThreadUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::SubThread::SubThread() :
	com_created_flg_(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SubThread::~SubThread()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::SubThread::Init(void)
{
	this->Release();

	tml::Thread::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::SubThread::Create(void)
{
	if (tml::Thread::Create(tml::ConstantUtil::THREAD::TYPE::SUB) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief CreateCOM�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::SubThread::CreateCOM(void)
{
	if (this->com_created_flg_) {
		return (0);
	}

	if (tml::ThreadUtil::CreateCOM(COINIT_MULTITHREADED) < 0) {
		return (-1);
	}

	this->com_created_flg_ = true;

	return (0);
}


/**
 * @brief DeleteCOM�֐�
 */
void tml::SubThread::DeleteCOM(void)
{
	if (!this->com_created_flg_) {
		return;
	}

	tml::ThreadUtil::DeleteCOM();

	this->com_created_flg_ = false;

	return;
}
