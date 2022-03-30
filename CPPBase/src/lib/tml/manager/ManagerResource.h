/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/INIFile.h"


namespace tml {
class Manager;
}


namespace tml {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc
{
private:
	tml::Manager *mgr_;

public:
	std::wstring resource_name;
	bool deferred_create_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);

	tml::Manager *GetManager(void) const;
	void SetManager(tml::Manager *);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::ManagerResourceDesc::SetManager(tml::Manager *mgr)
{
	this->OnSetManager(mgr);

	return;
}


namespace tml {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource
{
friend class tml::Manager;

public: ManagerResource(const tml::ManagerResource &) = delete;
public: tml::ManagerResource &operator =(const tml::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::unique_ptr<tml::ManagerResourceDesc> desc_unique_p_;
	const tml::ManagerResourceDesc *desc_;
	tml::Manager *mgr_;
	UINT res_type_;
	tml::shared_ptr<tml::ManagerResource> res_shared_p_;
	std::wstring res_name_;
	bool deferred_create_flg_;
	bool deferred_created_flg_;
	bool deferred_create_added_flg_;

private:
	void Release(void);

	void InitDeferredCreate(const bool);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	INT Create(void);
	INT CreateDeferred(void);

	const tml::ManagerResourceDesc *GetDesc(void) const;
	void SetDesc(const tml::ManagerResourceDesc *);
	tml::Manager *GetManager(void);
	void SetManager(tml::Manager *);
	UINT GetResourceType(void) const;
	const tml::shared_ptr<tml::ManagerResource> &GetResourceSharedPointer(void) const;
	const std::wstring &GetResourceName(void) const;
	bool GetDeferredCreateFlag(void) const;
	bool GetDeferredCreatedFlag(void) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::ManagerResourceDesc *tml::ManagerResource::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief SetDesc関数
 * @param desc (desc)
 */
inline void tml::ManagerResource::SetDesc(const tml::ManagerResourceDesc *desc)
{
	this->OnSetDesc(desc);

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::ManagerResource::SetManager(tml::Manager *mgr)
{
	this->OnSetManager(mgr);

	return;
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline UINT tml::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}


/**
 * @brief GetResourceSharedPointer関数
 * @return res_shared_p (resource_shared_pointer)
 */
inline const tml::shared_ptr<tml::ManagerResource> &tml::ManagerResource::GetResourceSharedPointer(void) const
{
	return (this->res_shared_p_);
}


/**
 * @brief GetResourceName関数
 * @return res_name (resource_name)
 */
inline const std::wstring &tml::ManagerResource::GetResourceName(void) const
{
	return (this->res_name_);
}


/**
 * @brief GetDeferredCreateFlag関数
 * @return deferred_create_flg (deferred_create_flag)
 */
inline bool tml::ManagerResource::GetDeferredCreateFlag(void) const
{
	return (this->deferred_create_flg_);
}


/**
 * @brief GetDeferredCreatedFlag関数
 * @return deferred_created_flg (deferred_created_flag)
 */
inline bool tml::ManagerResource::GetDeferredCreatedFlag(void) const
{
	return (this->deferred_created_flg_);
}
