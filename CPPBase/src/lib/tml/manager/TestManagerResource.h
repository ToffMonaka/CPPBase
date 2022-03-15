/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/INIFile.h"


namespace tml {
namespace test {
class Manager;
}
}


namespace tml {
namespace test {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc
{
private:
	tml::test::Manager *mgr_;

public:
	std::wstring resource_name;
	bool deferred_create_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);

	tml::test::Manager *GetManager(void) const;
	void SetManager(tml::test::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::test::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::test::ManagerResourceDesc::SetManager(tml::test::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


namespace tml {
namespace test {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource
{
friend class tml::test::Manager;

public: ManagerResource(const tml::test::ManagerResource &) = delete;
public: tml::test::ManagerResource &operator =(const tml::test::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::test::Manager *mgr_;
	tml::unique_ptr<tml::test::ManagerResourceDesc> desc_unique_p_;
	const tml::test::ManagerResourceDesc *desc_;
	UINT res_index_;
	tml::shared_ptr<tml::test::ManagerResource> res_shared_p_;
	std::wstring res_name_;
	bool deferred_create_flg_;
	bool deferred_created_flg_;
	bool deferred_create_added_flg_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	void SetManager(tml::test::Manager *);
	void SetDesc(const tml::test::ManagerResourceDesc *);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	INT Create(void);
	INT CreateDeferred(void);

	tml::test::Manager *GetManager(void);
	const tml::test::ManagerResourceDesc *GetDesc(void) const;
	UINT GetResourceIndex(void) const;
	const tml::shared_ptr<tml::test::ManagerResource> &GetResourceSharedPointer(void) const;
	const std::wstring &GetResourceName(void) const;
	bool GetDeferredCreateFlag(void) const;
	bool GetDeferredCreatedFlag(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::test::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::test::ManagerResource::SetManager(tml::test::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::test::ManagerResourceDesc *tml::test::ManagerResource::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief SetDesc関数
 * @param desc (desc)
 */
inline void tml::test::ManagerResource::SetDesc(const tml::test::ManagerResourceDesc *desc)
{
	this->desc_ = desc;

	return;
}


/**
 * @brief GetResourceIndex関数
 * @return res_index (resource_index)
 */
inline UINT tml::test::ManagerResource::GetResourceIndex(void) const
{
	return (this->res_index_);
}


/**
 * @brief GetResourceSharedPointer関数
 * @return res_shared_p (resource_shared_pointer)
 */
inline const tml::shared_ptr<tml::test::ManagerResource> &tml::test::ManagerResource::GetResourceSharedPointer(void) const
{
	return (this->res_shared_p_);
}


/**
 * @brief GetResourceName関数
 * @return res_name (resource_name)
 */
inline const std::wstring &tml::test::ManagerResource::GetResourceName(void) const
{
	return (this->res_name_);
}


/**
 * @brief GetDeferredCreateFlag関数
 * @return deferred_create_flg (deferred_create_flag)
 */
inline bool tml::test::ManagerResource::GetDeferredCreateFlag(void) const
{
	return (this->deferred_create_flg_);
}


/**
 * @brief GetDeferredCreatedFlag関数
 * @return deferred_created_flg (deferred_created_flag)
 */
inline bool tml::test::ManagerResource::GetDeferredCreatedFlag(void) const
{
	return (this->deferred_created_flg_);
}
