/**
 * @file
 * @brief SubThreadコードファイル
 */


#include "SubThread.h"


/**
 * @brief コンストラクタ
 */
tml::SubThread::SubThread()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::SubThread::~SubThread()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::SubThread::Init(void)
{
	tml::Thread::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::SubThread::Create(void)
{
	if (tml::Thread::Create(tml::ConstantUtil::THREAD::TYPE::SUB) < 0) {
		return (-1);
	}

	return (0);
}
