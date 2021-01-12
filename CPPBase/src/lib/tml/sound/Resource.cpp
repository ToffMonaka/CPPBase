/**
 * @file
 * @brief Resourceコードファイル
 */


#include "Resource.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ResourceDesc::~ResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::Resource::Resource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Resource::~Resource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::sound::Resource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Resource::Init(void)
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
INT tml::sound::Resource::Create(tml::sound::ResourceDesc &desc)
{
	if (desc.manager == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.manager;

	return (0);
}
