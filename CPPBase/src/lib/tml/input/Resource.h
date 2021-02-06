/**
 * @file
 * @brief Resourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../file/INIFile.h"


namespace tml {
namespace input {
class Manager;
}
}


namespace tml {
namespace input {
/**
 * @brief ResourceDescクラス
 */
class ResourceDesc
{
public:
	tml::input::Manager *manager;
	std::wstring name;

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ResourceDesc();
	ResourceDesc(tml::input::Manager *);
	virtual ~ResourceDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);
};
}
}


namespace tml {
namespace input {
/**
 * @brief Resourceクラス
 *
 * インターフェースパターン
 */
class Resource
{
public: Resource(const tml::input::Resource &) = delete;
public: tml::input::Resource &operator =(const tml::input::Resource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::INPUT::RESOURCE_TYPE res_type_;
	tml::input::Manager *mgr_;
	std::wstring name_;

protected:
	void Release(void);
	INT Create(const tml::input::ResourceDesc &, const tml::ConstantUtil::INPUT::RESOURCE_TYPE);

public:
	Resource();
	virtual ~Resource();

	virtual void Init(void);

	tml::ConstantUtil::INPUT::RESOURCE_TYPE GetResourceType(void) const;
	tml::input::Manager *GetManager(void);
	const std::wstring &GetName(void) const;
};
}
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::INPUT::RESOURCE_TYPE tml::input::Resource::GetResourceType(void) const
{
	return (this->res_type_);
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::Resource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::input::Resource::GetName(void) const
{
	return (this->name_);
}
