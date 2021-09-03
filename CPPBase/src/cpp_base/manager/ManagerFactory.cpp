/**
 * @file
 * @brief ManagerFactoryコードファイル
 */


#include "ManagerFactory.h"


/**
 * @brief コンストラクタ
 */
cpp_base::ManagerFactoryDesc::ManagerFactoryDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::ManagerFactoryDesc::~ManagerFactoryDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::ManagerFactoryDesc::Init(void)
{
	this->Release();

	tml::ManagerFactoryDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::ManagerFactory::ManagerFactory()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::ManagerFactory::Init(void)
{
	this->Release();

	tml::ManagerFactory::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::ManagerFactory::Create(const cpp_base::ManagerFactoryDesc &desc)
{
	this->Init();

	if (tml::ManagerFactory::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
