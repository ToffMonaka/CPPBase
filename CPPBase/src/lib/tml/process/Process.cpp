/**
 * @file
 * @brief Processコードファイル
 */


#include "Process.h"
#include "ProcessUtil.h"


/**
 * @brief コンストラクタ
 */
tml::Process::Process()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Process::~Process()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::Process::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::Process::Init(void)
{
	this->th_id_ = std::thread::id();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Process::Create(void)
{
	this->th_id_ = std::this_thread::get_id();

	return (0);
}
