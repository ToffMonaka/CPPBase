/**
 * @file
 * @brief ManagerFactoryコードファイル
 */


#include "ManagerFactory.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerFactory::Init(void)
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
INT tml::input::ManagerFactory::Create(tml::input::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
