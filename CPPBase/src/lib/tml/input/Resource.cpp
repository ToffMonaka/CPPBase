/**
 * @file
 * @brief Resourceコードファイル
 */


#include "Resource.h"


/**
 * @brief コンストラクタ
 */
tml::input::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ResourceDesc::~ResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::input::ResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::Resource::Resource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::Resource::~Resource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::input::Resource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::input::Resource::Init(void)
{
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Resource::Create(tml::input::ResourceDesc &desc)
{
	if (desc.manager == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.manager;

	return (0);
}
