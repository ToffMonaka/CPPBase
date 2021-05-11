/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::graphic::ManagerDesc::ManagerDesc()

{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::graphic::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::graphic::ManagerDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void cpp_base::graphic::ManagerDesc::InitResourceCount(void)
{
	tml::graphic::ManagerDesc::InitResourceCount();

	return;
}


/**
 * @brief InitEventCount関数
 */
void cpp_base::graphic::ManagerDesc::InitEventCount(void)
{
	tml::graphic::ManagerDesc::InitEventCount();

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::graphic::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::graphic::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::graphic::Manager::Release(void)
{
	this->DeleteCommon2();

	tml::graphic::Manager::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::graphic::Manager::Init(void)
{
	this->Release();

	tml::graphic::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::graphic::Manager::Create(const cpp_base::graphic::ManagerDesc &desc)
{
	this->Init();

	if (tml::graphic::Manager::Create(desc) < 0) {
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
INT cpp_base::graphic::Manager::CreateCommon2(void)
{
	if (this->common2.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon2関数
 */
void cpp_base::graphic::Manager::DeleteCommon2(void)
{
	this->common2.Init();

	return;
}
