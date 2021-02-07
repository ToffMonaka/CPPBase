/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::input::ManagerCommon::Release(void)
{
	if (this->mgr_ != nullptr) {
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::ManagerCommon::Create(tml::input::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
