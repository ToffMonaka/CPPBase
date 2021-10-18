/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ManagerCommon::Create(tml::sound::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
