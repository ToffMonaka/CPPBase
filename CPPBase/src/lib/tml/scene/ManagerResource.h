/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
private:
	tml::scene::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	tml::scene::Manager *GetManager(void) const;
	void SetManager(tml::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace scene {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::scene::ManagerResource &) = delete;
public: tml::scene::ManagerResource &operator =(const tml::scene::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::scene::Manager *mgr_;
	tml::ConstantUtil::SCENE::RESOURCE_TYPE res_type_;

private:
	void Release(void);

public:
	ManagerResource();
	virtual ~ManagerResource();
	INT Create(const tml::scene::ManagerResourceDesc &);

	virtual void Init(void);

	tml::scene::Manager *GetManager(void);
	tml::ConstantUtil::SCENE::RESOURCE_TYPE GetResourceType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::SCENE::RESOURCE_TYPE tml::scene::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}
