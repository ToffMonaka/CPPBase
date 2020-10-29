/**
 * @file
 * @brief MainProcessコードファイル
 */


#include "MainProcess.h"


/**
 * @brief コンストラクタ
 */
cpp_base::MainProcess::MainProcess()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::MainProcess::~MainProcess()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::MainProcess::Release(void)
{
	tml::Process::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::MainProcess::Init(void)
{
	this->Release();

	tml::Process::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainProcess::Create(void)
{
	this->Release();

	if (tml::Process::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
