/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace input {
class Manager;
}
}


namespace tml {
namespace input {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
public:
	tml::input::Manager *manager;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::ManagerResourceDesc::Release(void)
{
	tml::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace input {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::input::ManagerResource &) = delete;
public: tml::input::ManagerResource &operator =(const tml::input::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::input::Manager *mgr_;
	tml::ConstantUtil::INPUT::RESOURCE_TYPE res_type_;

protected:
	void Release(void);
	INT Create(const tml::input::ManagerResourceDesc &, const tml::ConstantUtil::INPUT::RESOURCE_TYPE, const UINT);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);

	tml::input::Manager *GetManager(void);
	tml::ConstantUtil::INPUT::RESOURCE_TYPE GetResourceType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::ManagerResource::Release(void)
{
	tml::ManagerResource::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::INPUT::RESOURCE_TYPE tml::input::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}
