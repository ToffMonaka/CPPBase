/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
private:
	tml::graphic::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void) const;
	void SetManager(tml::graphic::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::graphic::ManagerResource &) = delete;
public: tml::graphic::ManagerResource &operator =(const tml::graphic::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;
	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type_;

private:
	void Release(void);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	INT Create(const tml::graphic::ManagerResourceDesc &);

	tml::graphic::Manager *GetManager(void);
	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE GetResourceType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE tml::graphic::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}
