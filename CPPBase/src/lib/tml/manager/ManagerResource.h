/**
 * @file
 * @brief ManagerResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/INIFile.h"


namespace tml {
class Manager;
}


namespace tml {
/**
 * @brief ManagerResourceDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
/**
 * @brief ManagerResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
	tml::unique_ptr<tml::ManagerResourceDesc> deferred_create_desc_unique_p_;
	const tml::ManagerResourceDesc *deferred_create_desc_;
	bool deferred_created_flg_;

private:
	void Release(void);
	void ReleaseDeferred(void);

protected:
	virtual INT OnCreateDeferred(void);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	INT Create(const tml::ManagerResourceDesc &);
	virtual void InitDeferred(void);
	INT CreateDeferred(void);
	const tml::ManagerResourceDesc *GetDeferredCreateDesc(void) const;
	void SetDeferredCreateDesc(tml::unique_ptr<tml::ManagerResourceDesc> &);
	void SetDeferredCreateDesc(const tml::ManagerResourceDesc *);
	bool IsDeferredCreated(void) const;
	bool IsDeferredCreating(void) const;

	tml::Manager *GetManager(void);
	UINT GetResourceMainIndex(void) const;
	void SetResourceMainIndex(tml::Manager *, const UINT);
	UINT GetResourceSubIndex(void) const;
	void SetResourceSubIndex(tml::Manager *, const UINT);
	const tml::shared_ptr<tml::ManagerResource> &GetResourceSharedPointer(void) const;
	void SetResourceSharedPointer(tml::Manager *, const tml::shared_ptr<tml::ManagerResource> &);
	const std::wstring &GetResourceName(void) const;
	void SetResourceName(tml::Manager *, const WCHAR *);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::ManagerResource::Release(void)
{
	this->ReleaseDeferred();

	return;
}


/**
 * @brief ReleaseDeferred�֐�
 */
inline void tml::ManagerResource::ReleaseDeferred(void)
{
	return;
}


/**
 * @brief GetDeferredCreateDesc�֐�
 * @return deferred_create_desc (deferred_create_desc)
 */
inline const tml::ManagerResourceDesc *tml::ManagerResource::GetDeferredCreateDesc(void) const
{
	return (this->deferred_create_desc_);
}


/**
 * @brief SetDeferredCreateDesc�֐�
 * @return deferred_create_desc (deferred_create_desc)
 */
inline void tml::ManagerResource::SetDeferredCreateDesc(tml::unique_ptr<tml::ManagerResourceDesc> &deferred_create_desc)
{
	this->deferred_create_desc_unique_p_ = std::move(deferred_create_desc);
	this->deferred_create_desc_ = this->deferred_create_desc_unique_p_.get();

	return;
}


/**
 * @brief SetDeferredCreateDesc�֐�
 * @return deferred_create_desc (deferred_create_desc)
 */
inline void tml::ManagerResource::SetDeferredCreateDesc(const tml::ManagerResourceDesc *deferred_create_desc)
{
	this->deferred_create_desc_unique_p_.reset();
	this->deferred_create_desc_ = deferred_create_desc;

	return;
}


/**
 * @brief IsDeferredCreated�֐�
 * @return result_flg (result_flag)<br>
 * false=��쐬�ς�,true=�쐬�ς�
 */
inline bool tml::ManagerResource::IsDeferredCreated(void) const
{
	return (this->deferred_created_flg_);
}


/**
 * @brief IsDeferredCreating�֐�
 * @return result_flg (result_flag)<br>
 * false=��쐬��,true=�쐬��
 */
inline bool tml::ManagerResource::IsDeferredCreating(void) const
{
	return (false);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceMainIndex�֐�
 * @return res_main_index (resource_main_index)
 */
inline UINT tml::ManagerResource::GetResourceMainIndex(void) const
{
	return (this->res_main_index_);
}


/**
 * @brief GetResourceSubIndex�֐�
 * @return res_sub_index (resource_sub_index)
 */
inline UINT tml::ManagerResource::GetResourceSubIndex(void) const
{
	return (this->res_sub_index_);
}


/**
 * @brief GetResourceSharedPointer�֐�
 * @return res_shared_p (resource_shared_pointer)
 */
inline const tml::shared_ptr<tml::ManagerResource> &tml::ManagerResource::GetResourceSharedPointer(void) const
{
	return (this->res_shared_p_);
}


/**
 * @brief GetResourceName�֐�
 * @return res_name (resource_name)
 */
inline const std::wstring &tml::ManagerResource::GetResourceName(void) const
{
	return (this->res_name_);
}
