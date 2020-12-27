/**
 * @file
 * @brief SoundResourceコードファイル
 */


#include "SoundResource.h"


/**
 * @brief コンストラクタ
 */
tml::SoundResourceDesc::SoundResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::SoundResourceDesc::~SoundResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::SoundResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::SoundResource::SoundResource() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::SoundResource::~SoundResource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::SoundResource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::SoundResource::Init(void)
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
INT tml::SoundResource::Create(const tml::SoundResourceDesc &desc)
{
	this->mgr_ = desc.manager;

	return (0);
}
