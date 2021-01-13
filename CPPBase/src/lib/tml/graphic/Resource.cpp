/**
 * @file
 * @brief Resourceコードファイル
 */


#include "Resource.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ResourceDesc::~ResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ResourceDesc::Init(void)
{
	this->manager = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Resource::Resource() :
	res_type_(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Resource::~Resource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Resource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Resource::Init(void)
{
	this->res_type_ = tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE;
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
INT tml::graphic::Resource::Create(const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type, tml::graphic::ResourceDesc &desc)
{
	if ((res_type == tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;

	return (0);
}
