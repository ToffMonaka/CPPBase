/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::sound::ManagerDesc::ManagerDesc()

{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::sound::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::sound::ManagerDesc::Init(void)
{
	this->Release();

	tml::sound::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void cpp_base::sound::ManagerDesc::InitResourceCount(void)
{
	tml::sound::ManagerDesc::InitResourceCount();

	return;
}


/**
 * @brief InitEventCount関数
 */
void cpp_base::sound::ManagerDesc::InitEventCount(void)
{
	tml::sound::ManagerDesc::InitEventCount();

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::sound::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::sound::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::sound::Manager::Release(void)
{
	this->factory2.Init();
	this->common2.Init();

	tml::sound::Manager::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::sound::Manager::Init(void)
{
	this->Release();

	tml::sound::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::sound::Manager::Create(const cpp_base::sound::ManagerDesc &desc)
{
	this->Init();

	if (tml::sound::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (this->factory2.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
