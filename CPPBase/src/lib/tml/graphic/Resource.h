/**
 * @file
 * @brief Resource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../file/INIFile.h"


namespace tml {
namespace graphic {
class Manager;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ResourceDesc�N���X
 */
class ResourceDesc
{
public:
	tml::graphic::Manager *manager;
	std::wstring name;

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ResourceDesc();
	virtual ~ResourceDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Resource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Resource
{
public: Resource(const tml::graphic::Resource &) = delete;
public: tml::graphic::Resource &operator =(const tml::graphic::Resource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type_;
	tml::graphic::Manager *mgr_;
	std::wstring name_;

protected:
	void Release(void);
	INT Create(const tml::graphic::ResourceDesc &, const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE);

public:
	Resource();
	virtual ~Resource();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE GetResourceType(void) const;
	tml::graphic::Manager *GetManager(void);
	const std::wstring &GetName(void) const;
};
}
}


/**
 * @brief GetResourceType�֐�
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE tml::graphic::Resource::GetResourceType(void) const
{
	return (this->res_type_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::Resource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetName�֐�
 * @return name (name)
 */
inline const std::wstring &tml::graphic::Resource::GetName(void) const
{
	return (this->name_);
}
