/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerDesc::ManagerDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerDesc::~ManagerDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerDesc::Init(void)
{
	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::input::Manager::Release(void)
{
	for (auto &res_cont : this->res_cont_ary_) {
		for (auto &res : res_cont) {
			res->Init();
		}

		res_cont.clear();
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::input::Manager::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Manager::Create(tml::input::ManagerDesc &desc)
{
	this->Init();

	return (0);
}
