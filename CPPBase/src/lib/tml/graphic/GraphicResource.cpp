/**
 * @file
 * @brief GraphicResourceコードファイル
 */


#include "GraphicResource.h"


/**
 * @brief コンストラクタ
 */
tml::GraphicResourceDesc::GraphicResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::GraphicResourceDesc::~GraphicResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::GraphicResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::GraphicResource::GraphicResource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::GraphicResource::~GraphicResource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::GraphicResource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::GraphicResource::Init(void)
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
INT tml::GraphicResource::Create(const tml::GraphicResourceDesc &desc)
{
	this->mgr_ = desc.manager;

	return (0);
}
