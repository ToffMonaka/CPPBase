/**
 * @file
 * @brief TestThreadコードファイル
 */


#include "TestThread.h"
#include "../../lib/tml/time/TimeUtil.h"


/**
 * @brief コンストラクタ
 */
cpp_base::TestThread::TestThread()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::TestThread::~TestThread()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::TestThread::Release(void)
{
	this->DeleteCOM();

	tml::SubThread::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::TestThread::Init(void)
{
	this->Release();

	tml::SubThread::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::TestThread::Start(void)
{
	{// COM Create
		if (this->CreateCOM() < 0) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::TestThread::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::TestThread::Update(void)
{
	tml::TimeUtil::Sleep(tml::TIME_REAL(0.1));

	return;
}
