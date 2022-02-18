/**
 * @file
 * @brief ManagerResource�w�b�_�[�t�@�C��
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
 * @brief ManagerResourceDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::test::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace test {
/**
 * @brief ManagerResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerResource
{
friend class tml::test::Manager;

public: ManagerResource(const tml::test::ManagerResource &) = delete;
public: tml::test::ManagerResource &operator =(const tml::test::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::test::Manager *mgr_;
	UINT res_index_;
	tml::shared_ptr<tml::test::ManagerResource> res_shared_p_;
	std::wstring res_name_;

protected:
	tml::unique_ptr<tml::test::ManagerResourceDesc> deferred_create_desc_unique_p_;
	const tml::test::ManagerResourceDesc *deferred_create_desc_;
	bool deferred_created_flg_;
	bool deferred_creating_flg_;

private:
	void Release(void);
	void ReleaseDeferred(void);

protected:
	virtual INT OnCreateDeferred(void);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	INT Create(const tml::test::ManagerResourceDesc &);
	virtual void InitDeferred(void);
	INT CreateDeferred(void);
	const tml::test::ManagerResourceDesc *GetDeferredCreateDesc(void) const;
	bool IsDeferredCreated(void) const;
	bool IsDeferredCreating(void) const;

	tml::test::Manager *GetManager(void);
	UINT GetResourceIndex(void) const;
	const tml::shared_ptr<tml::test::ManagerResource> &GetResourceSharedPointer(void) const;
	const std::wstring &GetResourceName(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::test::ManagerResource::Release(void)
{
	this->ReleaseDeferred();

	return;
}


/**
 * @brief ReleaseDeferred�֐�
 */
inline void tml::test::ManagerResource::ReleaseDeferred(void)
{
	return;
}


/**
 * @brief GetDeferredCreateDesc�֐�
 * @return deferred_create_desc (deferred_create_desc)
 */
inline const tml::test::ManagerResourceDesc *tml::test::ManagerResource::GetDeferredCreateDesc(void) const
{
	return (this->deferred_create_desc_);
}


/**
 * @brief IsDeferredCreated�֐�
 * @return result_flg (result_flag)<br>
 * false=��쐬�ς�,true=�쐬�ς�
 */
inline bool tml::test::ManagerResource::IsDeferredCreated(void) const
{
	return (this->deferred_created_flg_);
}


/**
 * @brief IsDeferredCreating�֐�
 * @return result_flg (result_flag)<br>
 * false=��쐬��,true=�쐬��
 */
inline bool tml::test::ManagerResource::IsDeferredCreating(void) const
{
	return (this->deferred_creating_flg_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceIndex�֐�
 * @return res_index (resource_index)
 */
inline UINT tml::test::ManagerResource::GetResourceIndex(void) const
{
	return (this->res_index_);
}


/**
 * @brief GetResourceSharedPointer�֐�
 * @return res_shared_p (resource_shared_pointer)
 */
inline const tml::shared_ptr<tml::test::ManagerResource> &tml::test::ManagerResource::GetResourceSharedPointer(void) const
{
	return (this->res_shared_p_);
}


/**
 * @brief GetResourceName�֐�
 * @return res_name (resource_name)
 */
inline const std::wstring &tml::test::ManagerResource::GetResourceName(void) const
{
	return (this->res_name_);
}
