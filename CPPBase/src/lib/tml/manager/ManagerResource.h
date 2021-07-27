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
	bool deferred_load_flag;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

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


namespace tml {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource
{
public: ManagerResource(const tml::ManagerResource &) = delete;
public: tml::ManagerResource &operator =(const tml::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::Manager *mgr_;
	UINT res_main_index_;
	UINT res_sub_index_;
	tml::shared_ptr<tml::ManagerResource> res_shared_p_;
	std::wstring res_name_;

protected:
	tml::unique_ptr<tml::ManagerResourceDesc> load_desc_unique_p_;
	const tml::ManagerResourceDesc *load_desc_;
	bool loaded_flg_;

protected:
	void Release(void);
	INT Create(const tml::ManagerResourceDesc &, const UINT, const UINT);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	virtual INT Load(void);

	tml::Manager *GetManager(void);
	UINT GetResourceMainIndex(void) const;
	UINT GetResourceSubIndex(void) const;
	const tml::shared_ptr<tml::ManagerResource> &GetResourceSharedPointer(void) const;
	void SetResourceSharedPointer(tml::Manager *, const tml::shared_ptr<tml::ManagerResource> &);
	const std::wstring &GetResourceName(void) const;
	void SetResourceName(tml::Manager *, const WCHAR *);
	const tml::ManagerResourceDesc *GetLoadDesc(void) const;
	void SetLoadDesc(tml::unique_ptr<tml::ManagerResourceDesc> &);
	void SetLoadDesc(const tml::ManagerResourceDesc *);
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
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceMainIndex関数
 * @return res_main_index (resource_main_index)
 */
inline UINT tml::ManagerResource::GetResourceMainIndex(void) const
{
	return (this->res_main_index_);
}


/**
 * @brief GetResourceSubIndex関数
 * @return res_sub_index (resource_sub_index)
 */
inline UINT tml::ManagerResource::GetResourceSubIndex(void) const
{
	return (this->res_sub_index_);
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
 * @brief GetLoadDesc関数
 * @return load_desc (load_desc)
 */
inline const tml::ManagerResourceDesc *tml::ManagerResource::GetLoadDesc(void) const
{
	return (this->load_desc_);
}


/**
 * @brief SetLoadDesc関数
 * @return load_desc (load_desc)
 */
inline void tml::ManagerResource::SetLoadDesc(tml::unique_ptr<tml::ManagerResourceDesc> &load_desc)
{
	this->load_desc_unique_p_ = std::move(load_desc);
	this->load_desc_ = this->load_desc_unique_p_.get();

	return;
}


/**
 * @brief SetLoadDesc関数
 * @return load_desc (load_desc)
 */
inline void tml::ManagerResource::SetLoadDesc(const tml::ManagerResourceDesc *load_desc)
{
	this->load_desc_unique_p_.reset();
	this->load_desc_ = load_desc;

	return;
}
