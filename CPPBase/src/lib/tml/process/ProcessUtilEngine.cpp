/**
 * @file
 * @brief ProcessUtilEngineコードファイル
 */


#include "ProcessUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::ProcessUtilEngine::ProcessUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ProcessUtilEngine::~ProcessUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::ProcessUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ProcessUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ProcessUtilEngine::Create(void)
{
	return (0);
}


/**
 * @brief Start関数
 * @param proc (process)
 * @return res (result)<br>
 * 0未満=失敗,-2=多重起動
 */
INT tml::ProcessUtilEngine::Start(std::unique_ptr<tml::Process> &proc)
{
	return (0);
}


/**
 * @brief End関数
 */
void tml::ProcessUtilEngine::End(void)
{
	return;
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT tml::ProcessUtilEngine::GetExitCode(void)
{
	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
