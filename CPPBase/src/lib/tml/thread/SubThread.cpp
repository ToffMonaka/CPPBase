/**
 * @file
 * @brief SubThread�R�[�h�t�@�C��
 */


#include "SubThread.h"


/**
 * @brief �R���X�g���N�^
 */
tml::SubThread::SubThread()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SubThread::~SubThread()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::SubThread::Init(void)
{
	tml::Thread::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::SubThread::Create(void)
{
	if (tml::Thread::Create(tml::ConstantUtil::THREAD::TYPE::SUB) < 0) {
		return (-1);
	}

	return (0);
}
