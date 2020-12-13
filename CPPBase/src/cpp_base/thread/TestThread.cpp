/**
 * @file
 * @brief TestThreadコードファイル
 */


#include "TestThread.h"


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
	tml::SubThread::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::TestThread::Init(void)
{
	this->Release();

	this->frame_rate_.Init();

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
	this->Release();

	if (tml::SubThread::Create() < 0) {
		this->Init();

		return (-1);
	}

	this->frame_rate_.Init();

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::TestThread::Start(void)
{
	this->frame_rate_.Start(60U);

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
	this->frame_rate_.Update();

	return;
}
