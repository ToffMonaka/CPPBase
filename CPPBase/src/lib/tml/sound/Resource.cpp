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
	res_type_(tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE),
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
	this->res_type_ = tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE;
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param res_type (resource_type)
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Resource::Create(const tml::ConstantUtil::SOUND::RESOURCE_TYPE res_type, tml::sound::ResourceDesc &desc)
{
	if ((res_type == tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;

	return (0);
}
