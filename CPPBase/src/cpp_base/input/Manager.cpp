/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::input::ManagerDesc::ManagerDesc()

{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::input::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::input::ManagerDesc::Init(void)
{
	this->Release();

	tml::input::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void cpp_base::input::ManagerDesc::InitResourceCount(void)
{
	tml::input::ManagerDesc::InitResourceCount();

	return;
}


/**
 * @brief InitEventCount関数
 */
void cpp_base::input::ManagerDesc::InitEventCount(void)
{
	tml::input::ManagerDesc::InitEventCount();

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::input::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::input::Manager::Release(void)
{
	this->DeleteCommon2();

	tml::input::Manager::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::input::Manager::Init(void)
{
	this->Release();

	tml::input::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::input::Manager::Create(const cpp_base::input::ManagerDesc &desc)
{
	this->Init();

	if (tml::input::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (this->CreateCommon2() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief CreateCommon2関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::input::Manager::CreateCommon2(void)
{
	if (this->common2.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon2関数
 */
void cpp_base::input::Manager::DeleteCommon2(void)
{
	this->common2.Init();

	return;
}
