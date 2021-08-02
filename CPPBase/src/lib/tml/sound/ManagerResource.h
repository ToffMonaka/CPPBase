/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
private:
	tml::sound::Manager *mgr_;

public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	tml::sound::Manager *GetManager(void) const;
	void SetManager(tml::sound::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerResourceDesc::Release(void)
{
	tml::ManagerResourceDesc::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace sound {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::sound::ManagerResource &) = delete;
public: tml::sound::ManagerResource &operator =(const tml::sound::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::sound::Manager *mgr_;
	tml::ConstantUtil::SOUND::RESOURCE_TYPE res_type_;

protected:
	void Release(void);
	INT Create(const tml::sound::ManagerResourceDesc &);
	void ReleaseDeferred(void);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	virtual void InitDeferred(void);
	virtual INT OnCreateDeferred(void);

	tml::sound::Manager *GetManager(void);
	tml::ConstantUtil::SOUND::RESOURCE_TYPE GetResourceType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerResource::Release(void)
{
	tml::ManagerResource::Release();

	return;
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerResource::ReleaseDeferred(void)
{
	tml::ManagerResource::ReleaseDeferred();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::SOUND::RESOURCE_TYPE tml::sound::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}
