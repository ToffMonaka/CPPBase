/**
 * @file
 * @brief InputResourceコードファイル
 */


#include "InputResource.h"


/**
 * @brief コンストラクタ
 */
tml::InputResourceDesc::InputResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::InputResourceDesc::~InputResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::InputResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::InputResource::InputResource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::InputResource::~InputResource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::InputResource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::InputResource::Init(void)
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
INT tml::InputResource::Create(tml::InputResourceDesc &desc)
{
	if (desc.manager == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.manager;

	return (0);
}
